#include "list.h"

int main() {
    List<int> a;
    for (int i = 0; i < 7; ++i){
        a.append(i);
    }
    for (ListElement<int> val : a){
        std::cout << val.get_data() << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 7; ++i){
        std::cout << a[i] << " ";
    }
    return 0;
}
