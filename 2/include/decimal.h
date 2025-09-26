
#pragma once
#include "vector.h"
#include <string>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <cstddef>
#include <cctype>

class Decimal {
public:
    Decimal();
    Decimal(size_t n, unsigned char t = 0);
    Decimal(const std::string &s);
    Decimal(const Decimal &a);
    Decimal(Decimal&& a) noexcept;
    Decimal(const std::initializer_list<unsigned char> &t);
    ~Decimal();

    Decimal add(const Decimal &other) const;
    Decimal subtract(const Decimal &other) const;
    bool equals(const Decimal &other) const;
    bool is_greater(const Decimal &other) const;
    bool is_less(const Decimal &other) const;
    void print(std::ostream &os) const;

private:
    Vector array_;
    void normalize();
};