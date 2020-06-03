#include "Utils.h"

unsigned int factorial(unsigned int a) {
    if (a == 1) {
        return 1;
    } else {
        return a * factorial(a - 1);
    }
}