#ifndef COLLECTIONS_STUDENT_H
#define COLLECTIONS_STUDENT_H

    #include "Human.h"
    #include <iostream>

    class Student: public Human {
        private:
            std::string nameOfTheEduInstitution;
            int course;
            int groupNumber;
            float averageMark;
        public:
            Student();
            Student(std::string, int, int, int, int, std::string, int, int, float);
            void setNameOfTheEduInstitution(std::string);
            void setCourse(int);
            void setAverageMark(float);
            void setGroupNumber(int);
            std::string getNameOfTheEduInstitution();
            int getCourse();
            int getGroupNumber();
            float getAverageMark();
            ~Student();
            bool operator == (Student);
            friend std::ostream &operator<<(std::ostream &, Student);
    };

    Student::Student(std::string name, int weight, int height, int humanGender, int age, std::string nameOfTheEduInstitution, int course, int groupNumber, float averageMark): Human(name, weight, height, humanGender, age) {
        this->nameOfTheEduInstitution = nameOfTheEduInstitution;
        this->course = course;
        this->groupNumber = groupNumber;
        this->averageMark = averageMark;
    }

    void Student::setNameOfTheEduInstitution(std::string nameOfTheEduInstitution) {
        this->nameOfTheEduInstitution = nameOfTheEduInstitution;
    }

    void Student::setCourse(int course) {
        this->course = course;
    }

    void Student::setAverageMark(float avgMark) {
        this->averageMark = avgMark;
    }

    void Student::setGroupNumber(int groupNumber) {
        this->groupNumber = groupNumber;
    }

    std::string Student::getNameOfTheEduInstitution() {
        return this->nameOfTheEduInstitution;
    }

    int Student::getCourse() {
        return this->course;
    }

    int Student::getGroupNumber() {
        return this->groupNumber;
    }

    float Student::getAverageMark() {
        return this->averageMark;
    }

    std::ostream &operator<<(std::ostream &out, Student S) {
        out << "Student: {" << S.getName() << ", " << S.getAge() << ", " << S.getNameOfTheEduInstitution() << ", " << S.getCourse() << ", " << S.getGroupNumber() << ", " << S.getAverageMark() << "}";
        return out;
    }

bool Student::operator==(Student S) {
    return this->getName() == S.getName() && this->getAge() == S.getAge() &&
           this->getGender() == S.getGender() && this->getHeight() == S.getHeight() && this->getWeight() == S.getWeight() &&
            this->groupNumber == S.getGroupNumber() && this->course == S.getCourse();
}

Student::Student() = default;

    Student::~Student() = default;

#endif
