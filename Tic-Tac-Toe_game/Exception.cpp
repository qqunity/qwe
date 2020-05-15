#include "Exception.h"

#include <utility>

Exception::Exception(std::string errMsg, unsigned int lineWithErr, std::string fileWithErr) {
    this->errorMessage = "Error: " + errMsg + "\t\tLine: " + std::to_string(lineWithErr) + "\t\tFile: " +
                         fileWithErr;
}

const char *Exception::what() const noexcept {
    return this->errorMessage.c_str();
}

Exception::~Exception() = default;
