#include "decimal.h"

#include <cmath>
#include <stdexcept>

void Decimal::normalize() {
    while (array_.Size() > 1 && array_.Back() == 0) {
        array_.PopBack();
    }
}

int compare_magnitude(const Vector& a, const Vector& b) {
    if (a.Size() != b.Size()) {
        return a.Size() > b.Size() ? 1 : -1;
    }
    for (int i = static_cast<int>(a.Size()) - 1; i >= 0; --i) {
        if (a.Data()[i] != b.Data()[i]) {
            return a.Data()[i] > b.Data()[i] ? 1 : -1;
        }
    }
    return 0;
}

Decimal Decimal::add(const Decimal& a, const Decimal& b) {
    Decimal result_decimal;
    unsigned char carry = 0;
    size_t max_size = std::max(a.array_.Size(), b.array_.Size());
    result_decimal.array_.Reserve(max_size + 1);

    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char digit_a = (i < a.array_.Size()) ? a.array_.Data()[i] : 0;
        unsigned char digit_b = (i < b.array_.Size()) ? b.array_.Data()[i] : 0;
        unsigned char sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result_decimal.array_.PushBack(sum % 10);
    }
    result_decimal.normalize();
    return result_decimal;
}

Decimal Decimal::subtract(const Decimal& a, const Decimal& b) {
    if (a.is_less(b)) {
        throw std::invalid_argument("Subtraction would result in a negative number.");
    }
    Decimal result_decimal;
    result_decimal.array_.Reserve(a.array_.Size());
    int borrow = 0;
    for (size_t i = 0; i < a.array_.Size(); ++i) {
        int digit_a = a.array_.Data()[i];
        int digit_b = (i < b.array_.Size()) ? b.array_.Data()[i] : 0;
        
        int diff = digit_a - digit_b - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result_decimal.array_.PushBack(static_cast<unsigned char>(diff));
    }
    result_decimal.normalize();
    return result_decimal;
}

Decimal::Decimal() : array_{} {}

Decimal::Decimal(size_t n, unsigned char t) : array_(n, t) {
    if (n == 0) {
        array_.PushBack(0);
    }
    normalize();
}

Decimal::Decimal(const std::initializer_list<unsigned char> &t) : array_(t) {
    normalize();
}

Decimal::Decimal(const std::string& str) {
    std::string digits;
    for (char ch : str) {
        if (isdigit(ch)) digits += ch;
    }
    if (digits.empty()) {
        array_.PushBack(0);
    } else {
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            array_.PushBack(static_cast<unsigned char>(*it - '0'));
        }
    }
    normalize();
}

Decimal::Decimal(const Decimal &other) : array_(other.array_) {}

Decimal::Decimal(Decimal&& other) noexcept : array_(std::move(other.array_)) {}

Decimal::~Decimal() = default;

bool Decimal::equals(const Decimal &other) const {
    if (array_.Size() != other.array_.Size()) return false;
    for (size_t i = 0; i < array_.Size(); ++i) {
        if (array_.Data()[i] != other.array_.Data()[i]) return false;
    }
    return true;
}

bool Decimal::is_greater(const Decimal &other) const {
    return compare_magnitude(array_, other.array_) > 0;
}

bool Decimal::is_less(const Decimal &other) const {
    return compare_magnitude(array_, other.array_) < 0;
}

void Decimal::print(std::ostream &os) const {
    if (array_.IsEmpty()) {
        os << "0";
        return;
    }
    for (size_t i = array_.Size(); i > 0; --i) {
        os << static_cast<char>('0' + array_.Data()[i-1]);
    }
}