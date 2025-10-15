#include "vector.h"
#include <memory>
#include <utility>

// commit for pr
Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {
}

Vector::Vector(size_t count, Figure* value)
    : sz_(count), cap_(count < 10 ? 10 : count), arr_(alloc_.allocate(cap_)) {  
    for (size_t i = 0; i < count; ++i) {
        arr_[i] = value;
    }
}

Vector::Vector(const Vector& other)
    : alloc_(other.alloc_),
      sz_(other.sz_),
      cap_(other.cap_ < 10 ? 10 : other.cap_),  
      arr_(alloc_.allocate(cap_)) {             
    for (size_t i = 0; i < other.sz_; ++i) {
        arr_[i] = other.arr_[i];
    }
}

Vector::Vector(Vector&& other) noexcept
    : alloc_(std::move(other.alloc_)), sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
    other.arr_ = nullptr;
    other.sz_ = 0;
    other.cap_ = 0;
}

Vector::Vector(std::initializer_list<Figure*> init)
    : sz_(init.size()), cap_(init.size() < 10 ? 10 : init.size()), arr_(alloc_.allocate(cap_)) {
    size_t i = 0;
    for (Figure* ptr : init) {
        arr_[i++] = ptr;
    }
}

Figure*& Vector::Front() noexcept {
    return arr_[0];
}

const Figure* Vector::Front() const noexcept {
    return arr_[0];
}

bool Vector::IsEmpty() const noexcept {
    return sz_ == 0;
}

Figure*& Vector::Back() noexcept {
    return arr_[sz_ - 1];
}

const Figure* Vector::Back() const noexcept {
    return arr_[sz_ - 1];
}

Figure** Vector::Data() noexcept {
    return arr_;
}

const Figure* const* Vector::Data() const noexcept {
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
    
    Figure** new_arr = alloc_.allocate(new_cap);
    for (size_t i = 0; i < sz_; ++i) {
        new_arr[i] = arr_[i];
    }
    
    alloc_.deallocate(arr_, cap_);
    arr_ = new_arr;
    cap_ = new_cap;
}

void Vector::Clear() noexcept {
    sz_ = 0;
}

void Vector::Insert(size_t pos, Figure* value) {
    if (pos > sz_) {
        return;
    }
    
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }
    
    for (size_t i = sz_; i > pos; --i) {
        arr_[i] = arr_[i - 1];
    }
    
    arr_[pos] = value;
    ++sz_;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos >= end_pos || begin_pos >= sz_) {
        return;
    }
    
    if (end_pos > sz_) {
        end_pos = sz_;
    }
    
    size_t diff = end_pos - begin_pos;
    
    for (size_t i = begin_pos; i < sz_ - diff; ++i) {
        arr_[i] = arr_[i + diff];
    }
    
    sz_ -= diff;
}

void Vector::PushBack(Figure* value) {
    if (sz_ >= cap_) {
        Reserve(cap_ == 0 ? 1 : cap_ * 2);
    }
    
    arr_[sz_] = value;
    ++sz_;
}

void Vector::PopBack() {
    if (sz_ > 0) {
        --sz_;
    }
}

void Vector::Resize(size_t count, Figure* value) {
    if (count > cap_) {
        Reserve(count);
    }
    
    if (count > sz_) {
        for (size_t i = sz_; i < count; ++i) {
            arr_[i] = value;
        }
    }
    
    sz_ = count;
}

Figure*& Vector::operator[](size_t index) {
    return arr_[index];
}

const Figure* Vector::operator[](size_t index) const {
    return arr_[index];
}

double Vector::calculateTotalArea() const {
    double totalArea = 0.0;
    for (size_t i = 0; i < sz_; ++i) {
        if (arr_[i] != nullptr) {
            totalArea += static_cast<double>(*arr_[i]);
        }
    }
    return totalArea;
}

void Vector::removeFigure(size_t index) {
    if (index >= sz_) {
        return;
    }
    
    for (size_t i = index; i < sz_ - 1; ++i) {
        arr_[i] = arr_[i + 1];
    }
    --sz_;
}

Vector::~Vector() {
    alloc_.deallocate(arr_, cap_);
}