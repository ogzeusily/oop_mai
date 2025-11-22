#include <memory>

template <typename T>
Vector<T>::Vector() : sz_(0), cap_(0), arr_(nullptr) {
}

template <typename T>
Vector<T>::Vector(size_t count, const T& value)
    : sz_(count), cap_(count < 10 ? 10 : count), arr_(alloc_.allocate(cap_)) {  // NOLINT
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

template <typename T>
Vector<T>::Vector(const Vector& other)
    : alloc_(other.alloc_),
      sz_(other.sz_),
      cap_(other.cap_ < 10 ? 10 : other.cap_),  // NOLINT
      arr_(alloc_.allocate(cap_)) {             // NOLINT
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

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector tmp(other);
        std::swap(sz_, tmp.sz_);
        std::swap(cap_, tmp.cap_);
        std::swap(arr_, tmp.arr_);
        std::swap(alloc_, tmp.alloc_);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
    if (this != &other) {
        Clear();
        alloc_.deallocate(arr_, cap_);
        sz_ = other.sz_;
        cap_ = other.cap_;
        arr_ = other.arr_;
        alloc_ = std::move(other.alloc_);
        other.arr_ = nullptr;
        other.sz_ = 0;
        other.cap_ = 0;
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : alloc_(std::move(other.alloc_)), sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
    other.arr_ = nullptr;
    other.sz_ = 0;
    other.cap_ = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : sz_(init.size()), cap_(init.size() < 10 ? 10 : init.size()), arr_(alloc_.allocate(cap_)) {  // NOLINT
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

template <typename T>
T& Vector<T>::operator[](size_t pos) {
    return arr_[pos];
}

template <typename T>
const T& Vector<T>::operator[](size_t pos) const {
    return arr_[pos];
}

template <typename T>
T& Vector<T>::Front() const noexcept {
    return arr_[0];
}

template <typename T>
bool Vector<T>::IsEmpty() const noexcept {
    return sz_ == 0;
}

template <typename T>
T& Vector<T>::Back() const noexcept {
    return arr_[sz_ - 1];
}

template <typename T>
T* Vector<T>::Data() const noexcept {
    return arr_;
}

template <typename T>
size_t Vector<T>::Size() const noexcept {
    return sz_;
}

template <typename T>
size_t Vector<T>::Capacity() const noexcept {
    return cap_;
}

template <typename T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap <= cap_) {
        return;
    }
    T* new_arr = alloc_.allocate(new_cap);
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

template <typename T>
void Vector<T>::Clear() noexcept {
    for (size_t i = 0; i < sz_; ++i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }
    sz_ = 0;
}

template <typename T>
void Vector<T>::Insert(size_t pos, T value) {
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

template <typename T>
void Vector<T>::Erase(size_t begin_pos, size_t end_pos) {
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

template <typename T>
void Vector<T>::PushBack(T value) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }

    T* ptr = arr_ + sz_;
    try {
        std::allocator_traits<decltype(alloc_)>::construct(alloc_, ptr, std::move(value));
    } catch (...) {
        throw;
    }
    ++sz_;
}

template <typename T>
template <class... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }

    T* ptr = arr_ + sz_;
    try {
        std::allocator_traits<decltype(alloc_)>::construct(alloc_, ptr, std::forward<Args>(args)...);
    } catch (...) {
        throw;
    }
    ++sz_;
}

template <typename T>
void Vector<T>::PopBack() {
    --sz_;
    std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + sz_);
}

template <typename T>
void Vector<T>::Resize(size_t count, const T& value) {
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

template <typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < sz_; ++i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, arr_ + i);
    }
    alloc_.deallocate(arr_, cap_);
}