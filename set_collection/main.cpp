#include "animal.h"
#include <vector>
#include <algorithm>

int main() {
    Animal a;
    a.set_name("Gosha");
    a.set_height(104);
    a.set_type("tigr");
    Animal b;
    b.set_name("Pusya");
    b.set_height(205);
    b.set_type("koshka");
    Animal c;
    c.set_name("Leonid");
    c.set_height(50);
    c.set_type("pes");
    std::vector<Animal> vec;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    std::for_each(vec.begin(), vec.end(), [] (const Animal& A) {
        std::cout << A << " ";
    });
    std::sort(vec.begin(), vec.end(), [] (const Animal &A1, const Animal &A2) {
        return A1.get_height() > A2.get_height();
    });
    std::cout << std::endl;
    std::for_each(vec.begin(), vec.end(), [] (const Animal& A) {
        std::cout << A << " ";
    });
    std::cout << std::endl;
    auto filter = std::remove_if(vec.begin(), vec.end(), [] (const Animal& A) {
        return A.get_height() > 20 && A.get_height() < 120;
    });
    vec.erase(filter, vec.end());
    std::for_each(vec.begin(), vec.end(), [] (const Animal& A) {
        std::cout << A << " ";
    });
    return 0;
}
