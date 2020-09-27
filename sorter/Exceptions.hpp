#ifndef SORTER_EXCEPTIONS_HPP
#define SORTER_EXCEPTIONS_HPP


#include <exception>
#include <string>

namespace exceptions {
    class ArrayElementException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit ArrayElementException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~ArrayElementException() override;
    };

    class ListElementException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit ListElementException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~ListElementException() override;
    };

    class ArrayException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit ArrayException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~ArrayException() override;
    };

    class LinkedListException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit LinkedListException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~LinkedListException() override;
    };
}


#endif
