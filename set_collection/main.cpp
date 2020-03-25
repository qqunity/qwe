#include "animal.h"
#include "stream.h"
#include <vector>
#include <algorithm>
#include "sequence.h"

    class Car {
        private:
            std::string name;
        public:
            Car();
            ~Car() = default;
            Car(std::string);
            std::string get_name();
            virtual void say_hello() = 0;
    };

    Car::Car() {
        this->name = "default";
    }

    std::string Car::get_name() {
        return this->name;
    }

    Car::Car(std::string name) {
        this->name = name;
    }

    class BMW : public Car {
        private:
            std::string model;
        public:
            BMW();
            ~BMW() = default;
            void say_hello() override;
    };

    BMW::BMW() {
        this->model = "E12";
    }

    void BMW::say_hello() {
        std::cout << "Hello!";
    }


class Student {
    private:
        std::string name;
        int group_id;
    public:
        Student();
        Student(std::string, int);
        std::string get_name();
        int get_group_id();
        void set_name(std::string s_name);
        void set_group_id(int);
        friend std::ostream& operator<< (std::ostream &, const Student &);
        bool operator == (Student &);
};

    Student::Student(std::string s_name, int s_group_id) {
        this->name = s_name;
        this->group_id = s_group_id;
    }

    std::string Student::get_name() {
        return this->name;
    }

    int Student::get_group_id() {
        return this->group_id;
    }

    void Student::set_name(std::string s_name) {
        this->name = s_name;
    }

    void Student::set_group_id(int s_gruop_id) {
        this->group_id = s_gruop_id;
    }

    std::ostream &operator<<(std::ostream &out, const Student &S) {
        out << "<" << S.name << ", " << S.group_id << ">";
        return out;
    }

    Student::Student() {
        this->name = "null";
        this->group_id = -1;
    }

    bool Student::operator==(Student &S) {
        return this->name == S.name && this->group_id == S.group_id;
    }


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

void test_lab2(){
    int mas[] = {0, 1, 2, 3, 4, 5, 6, 7};
    MutableSequence<int, ListSequence<int>> s(mas, 8);
    int mas2[] = {0, 1, 2, 3, 4};
    MutableSequence<int, ListSequence<int>> s2(mas2, 5);
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
    int max_all = reduce<int>(s.begin(), s.end(), 0, [](int x1, int x2){
        return x1 > x2 ? x1 : x2;
    });
    std::cout << max_all << std::endl;
    std::cout << min_sequence_len<MutableSequence<int, ListSequence<int>>>(2, s, s2);
}

void test_student(){
    MutableSequence<Student, ArraySequence<Student>> ms;
    for (int i = 0; i < 3; ++i){
        Student st(Student("Vasya", i + 514));
        ms.append(st);
    }
    std::cout << ms << std::endl;
    auto n_ms = where<MutableSequence<Student, ArraySequence<Student>>>(ms.begin(), ms.end(), [](ArrayElement<Student> &ArrS){
        return ArrS.get_data().get_group_id() != 514;
    });
    std::cout << n_ms;
}

int main(){
    test_student();
//    ArraySequence<int> l;
//    for (int i = 0; i < 7; ++i){
//        l.append(i);
//    }
//    std::cout << l;
//    std::vector<Sequence<int> *> a;
//    a.push_back(&l);
//    std::cout << *dynamic_cast<ArraySequence<int> *>(a[0]);
    return 0;
}
