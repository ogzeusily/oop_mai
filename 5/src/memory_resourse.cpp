#include "memory_resourse.h"

#include <cstdint>

MemoryResource::MemoryResource(size_t pool_size): pool_size_(pool_size), pool_(new int8_t[pool_size]) {
}

MemoryResource::~MemoryResource() {
    delete[] pool_;
}

// align 'addr' up to 'alignment'
static inline std::uintptr_t align_up(std::uintptr_t addr, std::size_t alignment) {
    if (alignment <= 1) return addr;
    std::uintptr_t mask = static_cast<std::uintptr_t>(alignment) - 1;
    return (addr + mask) & ~mask;
}

void* MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (bytes == 0) {
        return nullptr;
    }

    // We'll search for a gap in the pool where an aligned block of 'bytes' fits.
    std::uintptr_t base = reinterpret_cast<std::uintptr_t>(pool_);
    std::size_t current_offset = 0;

    for (const auto& [ptr, size] : blocks_) {
        std::uintptr_t block_ptr = reinterpret_cast<std::uintptr_t>(ptr);
        std::size_t block_offset = static_cast<std::size_t>(block_ptr - base);

        // align start address within current gap
        std::uintptr_t candidate_addr = align_up(base + current_offset, alignment);
        std::size_t candidate_offset = static_cast<std::size_t>(candidate_addr - base);

        if (candidate_offset + bytes <= block_offset) {
            void* result = pool_ + candidate_offset;
            blocks_[result] = bytes;
            return result;
        }

        current_offset = block_offset + size;
    }

    // Try to allocate at the end of the pool
    std::uintptr_t candidate_addr = align_up(base + current_offset, alignment);
    std::size_t candidate_offset = static_cast<std::size_t>(candidate_addr - base);
    if (candidate_offset + bytes <= pool_size_) {
        void* result = pool_ + candidate_offset;
        blocks_[result] = bytes;
        return result;
    }

    throw std::bad_alloc();
}

void MemoryResource::do_deallocate(void* ptr, std::size_t bytes, std::size_t /*alignment*/) {
    auto it = blocks_.find(ptr);
    if (it == blocks_.end()) {
        throw InvalidDeallocatedBlockException("Unable to free unallocated memory");
    }
    if (it->second != bytes) {
        throw InvalidDeallocatedBitesSisezSizeException("Wrong block size to deallocate");
    }

    blocks_.erase(it);
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}