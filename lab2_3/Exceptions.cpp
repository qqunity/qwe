#include "Exceptions.hpp"

exceptions::ArrayElementException::ArrayElementException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::ArrayElementException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ArrayElementException::~ArrayElementException() = default;

exceptions::ListElementException::ListElementException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::ListElementException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ListElementException::~ListElementException() = default;

exceptions::ArrayException::ArrayException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::ArrayException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::ArrayException::~ArrayException() = default;


exceptions::LinkedListException::LinkedListException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::LinkedListException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::LinkedListException::~LinkedListException() = default;

exceptions::BTreeException::BTreeException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::BTreeException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::BTreeException::~BTreeException() = default;

exceptions::KVElementException::KVElementException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::KVElementException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::KVElementException::~KVElementException() = default;

exceptions::BTreeDictionaryException::BTreeDictionaryException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::BTreeDictionaryException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::BTreeDictionaryException::~BTreeDictionaryException() = default;

exceptions::IDictionaryException::IDictionaryException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::IDictionaryException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::IDictionaryException::~IDictionaryException() = default;

exceptions::AVLTreeDictionaryException::AVLTreeDictionaryException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::AVLTreeDictionaryException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::AVLTreeDictionaryException::~AVLTreeDictionaryException() = default;

exceptions::MatrixException::MatrixException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::MatrixException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::MatrixException::~MatrixException() = default;

exceptions::OptException::OptException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::OptException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::OptException::~OptException() = default;

exceptions::SparseVectorException::SparseVectorException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::SparseVectorException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::SparseVectorException::~SparseVectorException() = default;

exceptions::UndirectedGraphException::UndirectedGraphException(const std::string& errMessage, int line, const std::string& file) {
    this->errorMessage = "-Error in line " + std::to_string(line) +
                         " in file" + file + "-\t-" +
                         " Message: " + errMessage + "-";
}

const char *exceptions::UndirectedGraphException::what() const noexcept {
    return this->errorMessage.c_str();
}

exceptions::UndirectedGraphException::~UndirectedGraphException() = default;