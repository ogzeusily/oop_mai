#pragma once
#include <cstddef>
#include <memory>
#include <initializer_list>

class Vector {
public:
    Vector();
    Vector(size_t count, const unsigned char& value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<unsigned char> init);
    unsigned char& Front() const noexcept;
    unsigned char& Back() const noexcept;
    unsigned char* Data() const noexcept;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    void Reserve(size_t new_cap);
    void Clear() noexcept;
    void Insert(size_t pos, unsigned char value);
    void Erase(size_t begin_pos, size_t end_pos);
    void PushBack(unsigned char value);
    void PopBack();
    void Resize(size_t count, const unsigned char& value);
    ~Vector();
private:
    std::allocator<unsigned char> alloc_;
    size_t sz_;
    size_t cap_;
    unsigned char* arr_;
};