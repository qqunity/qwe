#include <iostream>
#include "array.h"
#include <string>

int main() {
    Array<int> a;
    for (int i = 0; i < 6; ++i){
        a.append(i);
    }
//    a.print_array();
    Array<int> b;
    b = a + a;
    b.print_array();
    return 0;
}
