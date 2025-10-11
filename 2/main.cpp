#include <iostream>
#include <string>
#include "decimal.h"
#include <stdexcept>

int main() {
    std::string a, b;

    std::cin >> a;
    std::cin >> b;

    Decimal decimal1(a);
    Decimal decimal2(b);

    Decimal sum = Decimal::add(decimal1, decimal2);

    std::cout << "\nSum: ";
    sum.print(std::cout);

    try {
        Decimal diff = Decimal::subtract(decimal1, decimal2);
        std::cout << "\nDifference: ";
        diff.print(std::cout);
    } catch (const std::invalid_argument& e) {
        std::cout << "\nError during subtraction: " << e.what();
    }

    std::cout << std::endl;
    return 0;
}