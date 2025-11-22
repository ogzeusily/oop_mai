#pragma once

#include <cstring>
#include <initializer_list>
#include <utility>

template <typename T>
class Vector {
public:
    Vector();

    Vector(size_t count, const T& value);

    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;

    Vector& operator=(Vector&& other);

    Vector(std::initializer_list<T> init);

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    T& Front() const noexcept;

    T& Back() const noexcept;

    T* Data() const noexcept;

    bool IsEmpty() const noexcept;

    size_t Size() const noexcept;

    size_t Capacity() const noexcept;

    void Reserve(size_t new_cap);  // NOLINT

    void Clear() noexcept;

    void Insert(size_t pos, T value);

    void Erase(size_t begin_pos, size_t end_pos);

    void PushBack(T value);

    template <class... Args>
    void EmplaceBack(Args&&... args);

    void PopBack();

    void Resize(size_t count, const T& value);

    ~Vector();

private:
    std::allocator<T> alloc_;
    size_t sz_;
    size_t cap_;
    T* arr_;
};

template <>
class Vector<void*> {
public:
    Vector() : sz_(0), cap_(0), arr_(nullptr) {
    }

    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;

    ~Vector() {
        Clear();
        delete[] arr_;
    }

    void PushBack(void* value) {
        if (sz_ >= cap_) {
            Reserve(cap_ == 0 ? 10 : cap_ * 2);  // NOLINT
        }
        arr_[sz_++] = value;
    }

    void* operator[](size_t pos) const {
        return arr_[pos];
    }

    size_t Size() const noexcept {
        return sz_;
    }
    size_t Capacity() const noexcept {
        return cap_;
    }

    void Clear() noexcept {
        for (size_t i = 0; i < sz_; ++i) {
            free(arr_[i]);
        }
        sz_ = 0;
    }

private:
    size_t sz_;
    size_t cap_;
    void** arr_;

    void Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }
        void** new_arr = new void*[new_cap];
        if (arr_) {
            std::memcpy(new_arr, arr_, sz_ * sizeof(void*));
            delete[] arr_;
        }
        arr_ = new_arr;
        cap_ = new_cap;
    }
};


namespace containers {

template <typename T>
using Vector = ::Vector<T>;

}
#include "vector.ipp"