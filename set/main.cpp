#include <iostream>
#include "set.cpp"
#include "list.h"

int main() {
    List<int> a;
    for (int i = 0; i < 6; ++i){
        a.append(i);
    }
    a.print_list();
    List b(a.reversed());
    b.print_list();
    b.set_element(2, 102);
    b.print_list();
    return 0;
}
