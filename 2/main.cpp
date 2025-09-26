#include <iostream>
#include <string>
#include "decimal.h"

int main() {
    std::string a, b;

    std::cout << "Enter a decimal1 number: ";
    std::cin >> a;
    std::cout << "\nEnter a decimal2 number: ";
    std::cin >> b;

    Decimal decimal1(a);
    Decimal decimal2(b);

    Decimal sum = decimal1.add(decimal2);
    Decimal diff = decimal1.subtract(decimal2);

    std::cout << "\nSum: ";
    sum.print(std::cout);

    std::cout << "\nDifference: ";
    diff.print(std::cout);

    std::cout << std::endl;
    return 0;
}