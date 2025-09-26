#include <iostream>
#include "separator.h"

int main() {
  int m, n;
  std::cout << "enter m value:";
  std::cin  >> m;
  std::cout << "enter n value:";
  std::cin  >> n;

  std::cout << "result: " << separator(m, n) << std::endl;

  return 0;
}