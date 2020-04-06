#ifndef COLLECTIONS_HUMAN_H
#define COLLECTIONS_HUMAN_H

    #include <string>

    enum gender {
        male = 1,
        female = -1
    };

    class Human {
        private:
            std::string name;
            int height;
            int weight;
            int humanGender;
            int age;
        public:
            Human();
            Human(std::string, int, int, int, int);
            void setName(std::string);
            void setHeight(int);
            void setGender(int);
            void setAge(int);
            std::string getName();
            int getHeight();
            int getWeight();
            int getGender();
            int getAge();
            ~Human();
    };

    Human::Human(std::string name, int weight, int height, int humanGender, int age) {
        this->name = name;
        this->weight = weight;
        this->height = height;
        this->humanGender = humanGender;
        this->age = age;
    }

    void Human::setName(std::string name) {
        this->name = name;
    }

    void Human::setHeight(int height) {
        this->height = height;
    }

    void Human::setGender(int gender) {
        this->humanGender = gender;
    }

    std::string Human::getName() {
        return this->name;
    }

    int Human::getHeight() {
        return this->height;
    }

    int Human::getWeight() {
        return this->weight;
    }

    int Human::getGender() {
        return this->humanGender;
    }

    void Human::setAge(int age) {
        this->age = age;
    }

    int Human::getAge() {
        return this->age;
    }

    Human::Human() = default;

Human::~Human() = default;

#endif
