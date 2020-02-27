#include <iostream>
#include "set.cpp"
#include "list.cpp"

int main() {
    List <int> a;
    for (int i = 0; i < 6; ++i){
        a.append(i);
    }
    a.pop(2);
    a.swap(1, 4);
    a.print_list();
    a.insert(4, 77);
    a.print_list();
    List <int> b;
    b = a;
    b.pop(3);
    b.insert(3, 77);
    a.print_list();
    b.print_list();
    std::cout << (a != b) << std::endl;
    List <int> c(a + b);
    c.print_list();
    std::cout << b.length();
    return 0;
}
