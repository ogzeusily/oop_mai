#include <iostream>
#include "separator.h"

int main() {
  int m, n;
  std::cin  >> m;
  std::cin  >> n;
  std::cout << separator(m, n) << std::endl;
  return 0;
}