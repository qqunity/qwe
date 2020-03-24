#ifndef SET_COLLECTION_ANIMAL_H
#define SET_COLLECTION_ANIMAL_H
    #include <utility>

#include "list.h"
    #include "string"

    class Animal{
        private:
            std::string a_name;
            int a_height;
            std::string a_type;
        public:
            Animal();
            Animal(const Animal&);
            ~Animal();
            std::string get_name();
            int get_height() const;
            std::string get_type();
            void set_name(std::string);
            void set_height(int);
            void set_type(std::string);
            bool operator > (const Animal&) const;
            bool operator >= (const Animal&) const;
            bool operator <= (const Animal&) const;
            bool operator < (const Animal&) const;
            friend std::ostream& operator<< (std::ostream &, const Animal &);
    };

    Animal::Animal() {
        this->a_name = "none";
        this->a_height = -1;
        this->a_type = "none";
    }

    Animal::Animal(const Animal &A) {
        this->a_name = A.a_name;
        this->a_height = A.a_height;
        this->a_type = A.a_type;
    }

    std::string Animal::get_name() {
        return this->a_name;
    }

    int Animal::get_height() const {
        return this->a_height;
    }

    std::string Animal::get_type() {
        return this->a_type;
    }

    void Animal::set_name(std::string name) {
        this->a_name = std::move(name);
    }

    void Animal::set_height(int height) {
        this->a_height = height;
    }

    void Animal::set_type(std::string type) {
        this->a_type = std::move(type);
    }

    bool Animal::operator>(const Animal &A) const {
        return this->a_height > A.a_height;
    }

    bool Animal::operator>=(const Animal &A) const {
        return this->a_height >= A.a_height;
    }

    bool Animal::operator<=(const Animal &A) const {
        return this->a_height <= A.a_height;
    }

    bool Animal::operator<(const Animal &A) const {
        return this->a_height < A.a_height;
    }

    std::ostream &operator<<(std::ostream &out, const Animal &A) {
        out << "<" << A.a_name << ", " << A.a_height << ", "  << A.a_type << ">";
        return out;
    }

    Animal::~Animal() = default;


#endif
