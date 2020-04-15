#include <iostream>
#include "BaseTest.h"
#include "Pair.h"
#include "Student.h"
#include <ctime>
#include "Teacher.h"
#include "Stream.h"
#include "Utils.h"

Student *randomStudent() {
    std::string mas[] = {"qwe", "asdas", "qweqweqwe"};
    array::Array<std::string> a(mas, 3);
    auto *st = new Student(a[rand() % 3], rand() % 2342, rand() % 123, 1, rand() % 123, "MEPhI", rand() % 4 + 1, rand() % 100, 0.5f);
    return st;
}


int main() {
//    std::cout << "Консольное тестирование базовых функций коллекции, выполненной в рамках лабораторной работы №2" << std::endl;
//    stream::Stream<Pair<Student, Teacher>> st(true, true, true, false, -1, "ArraySequence");
//    while (true){
//        std::cout << "\x1b[35m<o>\x1b[0m Введите 0, если хотите завершить консольное приложение." << std::endl << "\x1b[35m<o>\x1b[0m Введите 1, если хотите запустить unit-тесты." << std::endl << "\x1b[35m<o>\x1b[0m Введите 2, если хотите заполнить поток (stream)." << std::endl << "\x1b[35m<o>\x1b[0m Введите 3, если хотите вывести поток (stream) на экран." << std::endl << "\x1b[35m<o>\x1b[0m Введите 4, если хотите вывести только те пары (студент, преподаватель), у которых студен имеет определенный средний балл." << std::endl;
//        std::cout << "\x1b[35m-> \x1b[0m";
//        int userInput;
//        std::cin >> userInput;
//        if (userInput == 0) {
//            break;
//        }
//        else if (userInput == 1) {
//            startBaseTest();
//        }
//        else if (userInput == 2) {
//            std::cout << "\x1b[35m<o>\x1b[0m Вам предоставляется работа с данными в виде пары (студент, преподаватель). Следуйте ниже перечисленным инструкция, чтобы корректно заполнить данные." << std::endl;
//            std::cout << "\x1b[35m<o>\x1b[0m Введите количетво пар (студентов и преподавателей), с которыми мы будм работать." << std::endl;
//            std::cout << "\x1b[35m-> \x1b[0m";
//            int n;
//            std::cin >> n;
//            std::cout << "\x1b[35m<o>\x1b[0m Для каждого студента/преподавателя введите данные следуя инструкции, приведённой ниже." << std::endl;
//            for (int i = 1; i <= n; ++i){
//                std::cout << "\x1b[34m<o>\x1b[0m Информация по студенту "<< i <<":" << std::endl;
//                std::string studentName;
//                std::cout << "\x1b[34m<o>\x1b[0m Имя студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentName;
//                int studentWeight;
//                std::cout << "\x1b[34m<o>\x1b[0m Вес студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentWeight;
//                int studentHeight;
//                std::cout << "\x1b[34m<o>\x1b[0m Рост студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentHeight;
//                int studentGender;
//                std::cout << "\x1b[34m<o>\x1b[0m Пол студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentGender;
//                int studentAge;
//                std::cout << "\x1b[34m<o>\x1b[0m Возраст студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentAge;
//                std::string studentInstitute;
//                std::cout << "\x1b[34m<o>\x1b[0m Наименование университа студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentInstitute;
//                int studentCourse;
//                std::cout << "\x1b[34m<o>\x1b[0m Учебный курс студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentCourse;
//                int studentGroupNumber;
//                std::cout << "\x1b[34m<o>\x1b[0m Номер группы студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentGroupNumber;
//                float studentAvgMark;
//                std::cout << "\x1b[34m<o>\x1b[0m Средний балл студента" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> studentAvgMark;
//
//                std::cout << "\x1b[34m<o>\x1b[0m Информация по преподавателю "<< i <<":" << std::endl;
//                std::string teacherName;
//                std::cout << "\x1b[34m<o>\x1b[0m Имя преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherName;
//                int teacherWeight;
//                std::cout << "\x1b[34m<o>\x1b[0m Вес преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherWeight;
//                int teacherHeight;
//                std::cout << "\x1b[34m<o>\x1b[0m Рост преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherHeight;
//                int teacherGender;
//                std::cout << "\x1b[34m<o>\x1b[0m Пол преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherGender;
//                int teacherAge;
//                std::cout << "\x1b[34m<o>\x1b[0m Возраст преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherAge;
//                std::string teacherInstitute;
//                std::cout << "\x1b[34m<o>\x1b[0m Наименование университа преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherInstitute;
//                std::string teacherSubject;
//                std::cout << "\x1b[34m<o>\x1b[0m Наименование предмета преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherSubject;
//                int teacherNumberDepartament;
//                std::cout << "\x1b[34m<o>\x1b[0m Номер кафедры преподавателя" << std::endl << "\x1b[35m-> \x1b[0m";
//                std::cin >> teacherNumberDepartament;
//                st.push(Pair(Student(studentName, studentWeight, studentHeight, studentGender, studentAge, studentInstitute, studentCourse, studentGroupNumber, studentAvgMark), Teacher(teacherName, teacherWeight, teacherHeight, teacherGender, teacherAge, teacherInstitute, teacherSubject, teacherNumberDepartament)));
//            }
//        }
//        else if (userInput == 3) {
//            std::cout << "\x1b[35m<o>\x1b[0m Текущее состояние потока: " << std::endl;
//            std::cout << st << std::endl;
//        }
//        else if (userInput == 4) {
//            std::cout << "\x1b[34m<o>\x1b[0m Введите нижнее ограничение на средний балл" << std::endl << "\x1b[35m-> \x1b[0m";
//            float lowerLimit;
//            std::cin >> lowerLimit;
//            std::cout << "\x1b[34m<o>\x1b[0m Введите верхнее ограничение на средний балл" << std::endl << "\x1b[35m-> \x1b[0m";
//            float upperLimit;
//            std::cin >> upperLimit;
//            auto res = utils::where<array::Array<Pair<Student, Teacher>>>(st.begin<array::Array<Pair<Student, Teacher>>::ArrayIterator, arraySequence::ArraySequence<Pair<Student, Teacher>> *>(), st.end<array::Array<Pair<Student, Teacher>>::ArrayIterator, arraySequence::ArraySequence<Pair<Student, Teacher>> *>(), [upperLimit, lowerLimit] (Pair<Student, Teacher> P) {
//                return P.getFirst().getAverageMark() <= upperLimit && P.getFirst().getAverageMark() >= lowerLimit;
//            });
//            std::cout << res << std::endl;
//        }
//        else {
//            std::cout << "\x1b[35m<o>\x1b[0m Некорректный ввод повторите попытку." << std::endl;
//        }
//    }
//    std::cout << "До скорых встреч!";
    srand(time(NULL));
    list::List<Student *> l;
    for (int i = 0; i < 5; ++i) {
        l.append(randomStudent());
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << *l[i].getValue() << " ";
    }
    std::cout << std::endl;
    utils::map(l.begin(), l.end(), [](ListElement<Student *> &s) {
        s.getValue()->setAge(1000);
    });
    for (int i = 0; i < 5; ++i) {
        std::cout << *l[i].getValue() << " ";
    }
    std::cout << std::endl;
    return 0;
}
