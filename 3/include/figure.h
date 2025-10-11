#pragma once


#include <string>
#include <string_view>
#include <iostream>
class Figure
{

public:
    Figure() = default;
    virtual ~Figure();
    
    virtual void read(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;
    
    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.read(is);
        return is;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.print(os);
        return os;
    }

    virtual double surface() const = 0;
    virtual double perimeter() const = 0;
    
    virtual operator double() const {
        return surface();
    }
};
