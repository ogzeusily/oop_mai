#include "decimal.h"

#include <cmath>

void Decimal::normalize() {
    while (array_.Size() > 1 && array_.Back() == 0) {
        array_.PopBack();
    }
}

static int compare_magnitude(const Vector& a, const Vector& b) {
    if (a.Size() != b.Size()) {
        return a.Size() > b.Size() ? 1 : -1;
    }
    for (int i = static_cast<int>(a.Size()) - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return a[i] > b[i] ? 1 : -1;
        }
    }
    return 0;
}

static Vector add_vectors(const Vector& a, const Vector& b) {
    Vector result;
    unsigned char carry = 0;
    size_t max_size = std::max(a.Size(), b.Size());
    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char digit_a = (i < a.Size()) ? a[i] : 0;
        unsigned char digit_b = (i < b.Size()) ? b[i] : 0;
        unsigned char sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result.PushBack(sum % 10);
    }
    return result;
}

static Vector subtract_vectors(const Vector& a, const Vector& b) {
    Vector result;
    int borrow = 0;
    for (size_t i = 0; i < a.Size(); ++i) {
        int digit_a = a[i];
        int digit_b = (i < b.Size()) ? b[i] : 0;
        
        int diff = digit_a - digit_b - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.PushBack(static_cast<unsigned char>(diff));
    }
    return result;
}

Decimal::Decimal() : array_{} {}

Decimal::Decimal(size_t n, unsigned char t) : array_() {
    for (size_t i = 0; i < n; ++i) array_.PushBack(t);
}

Decimal::Decimal(const std::initializer_list<unsigned char> &t) : array_() {
    for(auto it = t.begin(); it != t.end(); ++it) {
        array_.PushBack(*it);
    }
}

Decimal::Decimal(const std::string& str) {
    std::string digits;
    for (char ch : str) {
        if (isdigit(ch)) digits += ch;
    }
    array_ = Vector();
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        array_.PushBack(static_cast<unsigned char>(*it - '0'));
    }
    normalize();
}

Decimal::Decimal(const Decimal &other) : array_(other.array_) {}

Decimal::Decimal(Decimal&& other) noexcept : array_(std::move(other.array_)) {}

Decimal::~Decimal() = default;

Decimal Decimal::add(const Decimal& other) const {
    Decimal result;
    result.array_ = add_vectors(array_, other.array_);
    result.normalize();
    return result;
}

Decimal Decimal::subtract(const Decimal& other) const {
    int cmp = compare_magnitude(array_, other.array_);
    if (cmp < 0) throw std::invalid_argument("Result would be negative");
    Decimal result;
    result.array_ = subtract_vectors(array_, other.array_);
    result.normalize();
    return result;
}

bool Decimal::equals(const Decimal &other) const {
    if (array_.Size() != other.array_.Size()) return false;
    for (size_t i = 0; i < array_.Size(); ++i) {
        if (array_[i] != other.array_[i]) return false;
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
    for (size_t i = array_.Size(); i > 0; --i) {
        os << static_cast<char>('0' + array_[i-1]);
    }
}