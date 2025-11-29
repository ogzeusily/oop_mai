#pragma once


class Point {
public:
    Point();
    Point(double x, double y);
    
    double GetX() const;
    double GetY() const;
    
    double Distance(const Point& other) const;

private:
    double x_;
    double y_;
};
