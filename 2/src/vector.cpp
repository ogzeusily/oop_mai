#include "vector.h"

#include <memory>


Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {
}


Vector::Vector(size_t count, const unsigned char& value)
    : sz_(count), cap_(count < 10 ? 10 : count), arr_(alloc_.allocate(cap_)) {  
    size_t i = 0;
    try {
        for (; i < count; ++i) {
            std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + i, value);
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + j);
        }
        alloc_.deallocate(arr_, cap_);
        throw;
    }
}


Vector::Vector(const Vector& other)
    : alloc_(other.alloc_),
      sz_(other.sz_),
      cap_(other.cap_ < 10 ? 10 : other.cap_),  
      arr_(alloc_.allocate(cap_)) {             
    size_t i = 0;
    try {
        for (; i < other.sz_; ++i) {
            std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + i, other.arr_[i]);
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + j);
        }
        alloc_.deallocate(arr_, cap_);
        throw;
    }
}


Vector::Vector(Vector&& other) noexcept
    : alloc_(std::move(other.alloc_)), sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
    other.arr_ = nullptr;
    other.sz_ = 0;
    other.cap_ = 0;
}


Vector::Vector(std::initializer_list<unsigned char> init)
    : sz_(init.size()), cap_(init.size() < 10 ? 10 : init.size()), arr_(alloc_.allocate(cap_)) {
    size_t i = 0;
    try {
        for (const auto& item : init) {
            std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + i, item);
            ++i;
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + j);
        }
        alloc_.deallocate(arr_, cap_);
        throw;
    }
}

unsigned char& Vector::Front() const noexcept {
    return arr_[0];
}


bool Vector::IsEmpty() const noexcept {
    return sz_ == 0;
}


unsigned char& Vector::Back() const noexcept {
    return arr_[sz_ - 1];
}


unsigned char* Vector::Data() const noexcept {
    return arr_;
}


size_t Vector::Size() const noexcept {
    return sz_;
}


size_t Vector::Capacity() const noexcept {
    return cap_;
}


void Vector::Reserve(size_t new_cap) {
    if (new_cap <= cap_) {
        return;
    }
    unsigned char* new_arr = alloc_.allocate(new_cap);
    size_t i = 0;
    try {
        for (; i < sz_; ++i) {
            std::allocator_traits<decltype(alloc_)>::construct(alloc_, new_arr + i, std::move_if_noexcept(arr_[i]));
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            std::allocator_traits<decltype(alloc_)>::destroy(alloc_, new_arr + j);
        }
        alloc_.deallocate(new_arr, new_cap);
        throw;
    }

    for (size_t j = 0; j < sz_; ++j) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + j);
    }
    alloc_.deallocate(arr_, cap_);

    arr_ = new_arr;
    cap_ = new_cap;
}


void Vector::Clear() noexcept {
    for (size_t i = 0; i < sz_; ++i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }
    sz_ = 0;
}


void Vector::Insert(size_t pos, unsigned char value) {
    if (pos > sz_) {
        return;
    }
    if (sz_ + 1 > cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }

    for (size_t i = sz_; i > pos; --i) {
        std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + i, std::move(arr_[i - 1]));
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i - 1);
    }

    std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + pos, std::move(value));
    ++sz_;
}


void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos > end_pos || begin_pos > sz_) {
        return;
    }
    size_t diff = end_pos - begin_pos;
    if (diff == 0) {
        return;
    }

    for (size_t i = begin_pos; i < end_pos; ++i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }

    for (size_t i = end_pos; i < sz_; ++i) {
        std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + begin_pos + (i - end_pos),
                                                           std::move_if_noexcept(arr_[i]));
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }
    sz_ -= diff;
}


void Vector::PushBack(unsigned char value) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }

    unsigned char* ptr = arr_ + sz_;
    try {
        std::allocator_traits<decltype(alloc_)>::construct(alloc_, ptr, std::move(value));
    } catch (...) {
        throw;
    }
    ++sz_;
}

void Vector::PopBack() {
    --sz_;
    std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + sz_);
}

void Vector::Resize(size_t count, const unsigned char& value) {
    if (count > cap_) {
        Reserve(count);
    }

    if (count > sz_) {
        for (size_t i = sz_; i < count; ++i) {
            std::allocator_traits<decltype(alloc_)>::construct(alloc_, arr_ + i, value);
        }
    } else {
        for (size_t i = count; i < sz_; ++i) {
            std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
        }
    }
    sz_ = count;
}

Vector::~Vector() {
    for (size_t i = 0; i < sz_; ++i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }
    alloc_.deallocate(arr_, cap_);
}