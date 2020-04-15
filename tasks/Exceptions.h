#pragma once
#ifndef TASKS_EXCEPTIONS_H
#define TASKS_EXCEPTIONS_H
    #include <exception>
    #include <string>

    class ListElementException : public std::exception {
        private:
            std::string errorMessage;
        public:
            ListElementException(std::string error);

            const char *what() const noexcept override;

            ~ListElementException();
    };

    ListElementException::ListElementException(std::string error) {
        this->errorMessage = std::move(error);
    }

    const char *ListElementException::what() const noexcept {
        return this->errorMessage.c_str();
    }

    ListElementException::~ListElementException() = default;

    class ListException: public std::exception {
    private:
        std::string errorMessage;
    public:
        ListException(std::string error);

        const char *what() const noexcept override;

        ~ListException();
    };

    ListException::ListException(std::string error) {
        this->errorMessage = std::move(error);
    }

    const char *ListException::what() const noexcept {
        return this->errorMessage.c_str();
    }

    ListException::~ListException() = default;
#endif
