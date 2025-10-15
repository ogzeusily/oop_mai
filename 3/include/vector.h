#pragma once
#include <cstddef>
#include <memory>
#include <initializer_list>
#include "figure.h"

// commit for pr
class Vector {
public:
    Vector();
    Vector(size_t count, Figure* value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<Figure*> init);
    Figure*& Front() noexcept;
    const Figure* Front() const noexcept;
    Figure*& Back() noexcept;
    const Figure* Back() const noexcept;
    Figure** Data() noexcept;
    const Figure* const* Data() const noexcept;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    void Reserve(size_t new_cap);
    void Clear() noexcept;
    void Insert(size_t pos, Figure* value);
    void Erase(size_t begin_pos, size_t end_pos);
    void PushBack(Figure* value);
    void PopBack();
    void Resize(size_t count, Figure* value);
    
    Figure*& operator[](size_t index);
    const Figure* operator[](size_t index) const;
    
    double calculateTotalArea() const;
    void removeFigure(size_t index);
    
    ~Vector();
private:
    std::allocator<Figure*> alloc_;
    size_t sz_;
    size_t cap_;
    Figure** arr_;
};