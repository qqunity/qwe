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

    class BTreeException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit BTreeException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~BTreeException() override;
    };

    class KVElementException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit KVElementException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~KVElementException() override;
    };

    class BTreeDictionaryException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit BTreeDictionaryException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~BTreeDictionaryException() override;
    };

    class IDictionaryException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit IDictionaryException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~IDictionaryException() override;
    };

    class AVLTreeDictionaryException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit AVLTreeDictionaryException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~AVLTreeDictionaryException() override;
    };

    class MatrixException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit MatrixException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~MatrixException() override;
    };

    class OptException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit OptException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~OptException() override;
    };

    class GameException : public std::exception {
    private:
        std::string errorMessage;
    public:
        explicit GameException(const std::string& errMessage, int line, const std::string& file);

        [[nodiscard]] const char *what() const noexcept override;

        ~GameException() override;
    };
}



#endif
