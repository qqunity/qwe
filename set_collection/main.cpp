#include "animal.h"

int main() {
    Animal a;
    a.set_name("Gosha");
    a.set_height(104);
    a.set_type("tigr");
    Animal b;
    b.set_name("Pusya");
    b.set_height(205);
    b.set_type("koshka");
    List<Animal> l;
    l.append(a);
    l.append(b);
    std::cout << l << std::endl;
    List<Animal> ls(l.sorted("DESC"));
    std::cout << ls;
    return 0;
}
