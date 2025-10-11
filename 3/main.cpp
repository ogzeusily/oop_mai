#include <iostream>
#include <memory>
#include "vector.h"
#include "triangle.h"
#include "rectangle.h"
#include "kvadrat.h"

int main() {
    Vector figures;
    
    Triangle* triangle = new Triangle(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
    figures.PushBack(triangle);
    
    Rectangle* rectangle = new Rectangle(Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3));
    figures.PushBack(rectangle);
    
    Kvadrat* kvadrat = new Kvadrat(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));
    figures.PushBack(kvadrat);
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << *figures[i] << std::endl;
    }
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << static_cast<double>(*figures[i]) << std::endl;
    }
    
    std::cout << figures.calculateTotalArea() << std::endl;
    
    Triangle triangleCopy = *triangle;
    
    bool areEqual = (*triangle == triangleCopy);
    
    Triangle triangleMoved = std::move(triangleCopy);
    
    std::cout << figures.Size() << std::endl;
    
    if (figures.Size() > 1) {
        delete figures[1];
        figures.removeFigure(1);
    }
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << *figures[i] << std::endl;
    }
    
    std::cout << figures.calculateTotalArea() << std::endl;
    
    for (size_t i = 0; i < figures.Size(); ++i) {
        delete figures[i];
    }
    
    return 0;
}