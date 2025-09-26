#include "separator.h"

int separator(int m,int n) {
    int result;
    result = ((m > 0 && n > 0) ? m + n - 2 : 0);  // если какое-то число <= 0 -> выводим 0
    return result;
}