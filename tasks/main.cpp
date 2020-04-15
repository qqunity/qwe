#include <iostream>
#include "List.h"

int main() {
    List<int> l;
    for(int i = 0; i < 7; ++i){
        l.append(i);
    }
    List<int> l2 (l);
    l2[5] = 8738453;
    std::cout << l << std::endl << l2 << std::endl  << (l != l2);
    return 0;
}
