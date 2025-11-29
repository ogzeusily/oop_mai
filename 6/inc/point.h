#pragma once

class Point {
private:
    double x;
    double y;

public:
    Point(double x = 0, double y = 0);
    
    double getX() const;
    double getY() const;
    
    void setX(double x);
    void setY(double y);
    
    double distance(const Point& other) const;
};
