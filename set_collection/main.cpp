#include "binary_heap.h"

int main() {
    Array<int> a;
    int n;
    std::cin >> n;
    int buff;
    for (int i = 0; i < n; ++i){
        std::cin >> buff;
        a.append(buff);
    }
    BinaryHeap<int> b(a);
    Array<int> c;
    for (int i = 0; i < a.length(); ++i){
        c.append(b.extract_min());
    }
    c.print_array();
    return 0;
}
