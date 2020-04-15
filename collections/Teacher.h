#ifndef COLLECTIONS_TEACHER_H
#define COLLECTIONS_TEACHER_H
    #include "Human.h"
    #include <iostream>

    class Teacher: public Human {
        private:
            std::string nameOfTheEduInstitution;
            std::string subjectOfTeaching;
            int departmentNumber;
        public:
            Teacher();
            Teacher(std::string, int, int, int, int, std::string, std::string, int);
            void setNameOfTheEduInstitution(std::string);
            void setSubjectOfTeaching(std::string);
            void setDepartmentNumber(int);
            std::string getNameOfTheEduInstitution();
            std::string getSubjectOfTeaching();
            int getDepartmentNumber();
            ~Teacher();
            bool operator == (Teacher);
            friend std::ostream &operator<<(std::ostream &, Teacher);
    };

    Teacher::Teacher(std::string name, int weight, int height, int humanGender, int age, std::string nameOfTheEduInstitution, std::string subjectOfTeaching, int departmentNumber): Human(name, weight, height, humanGender, age) {
        this->nameOfTheEduInstitution = nameOfTheEduInstitution;
        this->departmentNumber = departmentNumber;
        this->subjectOfTeaching = subjectOfTeaching;
    }

    void Teacher::setNameOfTheEduInstitution(std::string nameOfTheEduInstitution) {
        this->nameOfTheEduInstitution = nameOfTheEduInstitution;
    }

    void Teacher::setSubjectOfTeaching(std::string subjectOfTeaching) {
        this->subjectOfTeaching = subjectOfTeaching;
    }

    void Teacher::setDepartmentNumber(int departmentNumber) {
        this->departmentNumber = departmentNumber;
    }

    std::string Teacher::getNameOfTheEduInstitution() {
        return this->nameOfTheEduInstitution;
    }

    std::string Teacher::getSubjectOfTeaching() {
        return this->subjectOfTeaching;
    }

    int Teacher::getDepartmentNumber() {
        return this->departmentNumber;
    }

    std::ostream &operator<<(std::ostream &out, Teacher T) {
        out << "Teacher: {" << T.getName() << ", " << T.getAge() << ", " << T.getNameOfTheEduInstitution() << ", " << T.getSubjectOfTeaching() << ", " << T.getDepartmentNumber() << "}";
        return out;
    }

    bool Teacher::operator==(Teacher T) {
        return this->departmentNumber == T.getDepartmentNumber() && this->subjectOfTeaching == T.subjectOfTeaching &&
                this->nameOfTheEduInstitution == T.nameOfTheEduInstitution && this->getName() == T.getName() && this->getAge() == T.getAge() &&
                this->getGender() == T.getGender() && this->getHeight() == T.getHeight() && this->getWeight() == T.getWeight();
    }

Teacher::Teacher() = default;

    Teacher::~Teacher() = default;


#endif
