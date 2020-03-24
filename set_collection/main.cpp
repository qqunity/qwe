#include "animal.h"
#include "stream.h"
#include <vector>
#include <algorithm>


void test_lambda(){
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
}

int main() {
    int mas[] = {0, 1, 2, 3, 4, 5, 6, 7};
    MutableSequence<int, ListSequence<int>> s(mas, 8);
    std::cout << s << std::endl;
    int init = 9;
    map(s.begin(), s.end(), [&init](ListElement<int> &val){
       val.set_data(init);
       ++init;
    });
    std::cout << s << std::endl;
    auto ms = where<MutableSequence<int, ListSequence<int>>>(s.begin(), s.end(), [](ListElement<int> &val){
        return val.get_data() < 13;
    });
    std::cout << ms << std::endl;
    int sum_all = reduce<int>(s.begin(), s.end(), 0, [](int x1, int x2){
        return x1 > x2 ? x1 : x2;
    });
    std::cout << sum_all << std::endl;
}
