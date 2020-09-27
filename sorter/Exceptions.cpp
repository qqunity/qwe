#include "Exceptions.hpp"

exceptions::ArrayElementException::ArrayElementException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message:" + errMessage + "-";
}

const char *exceptions::ArrayElementException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ArrayElementException::~ArrayElementException() = default;

exceptions::ListElementException::ListElementException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message:" + errMessage + "-";
}

const char *exceptions::ListElementException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ListElementException::~ListElementException() = default;

exceptions::ArrayException::ArrayException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message:" + errMessage + "-";
}

const char *exceptions::ArrayException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ArrayException::~ArrayException() = default;


exceptions::LinkedListException::LinkedListException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message:" + errMessage + "-";
}

const char *exceptions::LinkedListException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::LinkedListException::~LinkedListException() = default;