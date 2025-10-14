#pragma once
#include "rectangle.h"

// commit for pr
class Kvadrat : public Rectangle {
public:
    Kvadrat() = delete;
    Kvadrat(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Kvadrat(const Kvadrat& other);
    Kvadrat(Kvadrat&& other) noexcept;
    
    Kvadrat& operator=(const Kvadrat& other);
    Kvadrat& operator=(Kvadrat&& other) noexcept;
    bool operator==(const Kvadrat& other) const;
    
    void read(std::istream& is) override;
    void print(std::ostream& os) const override;
};