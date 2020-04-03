#ifndef COLLECTIONS_EXCEPTIONS_H
#define COLLECTIONS_EXCEPTIONS_H
    #include <exception>
    #include <string>
    #include <utility>

    namespace arrayException {
        class ArrayElementException : public std::exception {
            private:
                std::string errorMessage;
            public:
                explicit ArrayElementException(std::string);

                const char *what() const noexcept override;

                ~ArrayElementException();
        };

        ArrayElementException::ArrayElementException(std::string error) {
            this->errorMessage = std::move(error);
        }

        const char *ArrayElementException::what() const noexcept {
            return this->errorMessage.c_str();
        }

        ArrayElementException::~ArrayElementException() = default;

        class ArrayException: public std::exception {
            private:
                std::string errorMessage;
            public:
                ArrayException(std::string);

                const char *what() const noexcept override;

                ~ArrayException();
        };

        ArrayException::ArrayException(std::string error) {
            this->errorMessage = std::move(error);
        }

        const char *ArrayException::what() const noexcept {
            return this->errorMessage.c_str();
        }

        ArrayException::~ArrayException() = default;
    }

    namespace listException {
        class ListElementException : public std::exception {
        private:
            std::string errorMessage;
        public:
            explicit ListElementException(std::string);

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
                ListException(std::string);

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
    }

    namespace streamException {
        class StreamException: public std::exception {
        private:
            std::string errorMessage;
        public:
            StreamException(std::string);

            const char *what() const noexcept override;

            ~StreamException();
        };

        StreamException::StreamException(std::string error) {
            this->errorMessage = std::move(error);
        }

        const char *StreamException::what() const noexcept {
            return this->errorMessage.c_str();
        }

        StreamException::~StreamException() = default;
    }

#endif
