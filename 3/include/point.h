#pragma once

#include <iostream>
#include <cmath>

class Point {
public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point(const Point& other) : x(other.x), y(other.y) {}
    
    Point(Point&& other) noexcept : x(other.x), y(other.y) {
        other.x = 0;
        other.y = 0;
    }
    
    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    
    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            other.x = 0;
            other.y = 0;
        }
        return *this;
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    void setX(double x) { x = x; }
    void setY(double y) { y = y; }
    
    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

private:
    double x, y;
};