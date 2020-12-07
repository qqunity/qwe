#ifndef SORTER_ARRAY_HPP
#define SORTER_ARRAY_HPP

#include "ArrayElement.hpp"

namespace array {
    template<typename T>
    class Array {
    private:
        ArrayElement<T> *data;
        unsigned int size;
    public:
        Array();

        Array(T *mas, unsigned int size);

        explicit Array(unsigned int size);

        Array(const Array<T> &arr);

        void append(T value);

        void prepend(T value);

        void pop(unsigned int index);

        void remove();

        void swap(unsigned int index1, unsigned int index2);

        T &getElement(unsigned int index);

        int getIndex(T value);

        void resize(unsigned int size);

        unsigned int length();

        ArrayElement<T> *getFirst();

        ArrayElement<T> *getLast();

        void insert(unsigned int index, T value);

        Array<T> &operator=(const Array<T> &arr);

        Array<T> operator+(const Array<T> &arr);

        Array<T> operator*(unsigned int c);

        ArrayElement<T> *operator[](unsigned int index);

        bool operator==(const Array<T> &arr);

        ~Array();

        class ArrayIterator {
        private:
            ArrayElement<T> *curObj;
        public:
            ArrayIterator(ArrayElement<T> *obj) {
                this->curObj = obj;
            }

            ArrayElement<T> &operator+(int k) {
                return *(this->curObj + k);
            }

            ArrayElement<T> &operator-(int k) {
                return *(this->curObj - k);
            }

            int operator-(const ArrayIterator &arrIt) {
                int i = 0;
                ArrayIterator buffIt = arrIt;
                while (buffIt != *this) {
                    ++i;
                    ++buffIt;
                }
                return i;
            }

            ArrayElement<T> operator++(int) {
                return *this->curObj++;
            }

            ArrayElement<T> operator--(int) {
                return *this->curObj--;
            }

            ArrayElement<T> &operator++() {
                return *++this->curObj;
            }

            ArrayElement<T> &operator--() {
                return *--this->curObj;
            }

            ArrayIterator &operator=(ArrayElement<T> arrEl) {
                this->curObj = &arrEl;
                return *this;
            }

            bool operator==(const ArrayIterator &arrIt) {
                return this->curObj == arrIt.curObj;
            }

            ArrayElement<T> &operator*() {
                return *this->curObj;
            }
        };

        ArrayIterator begin();

        ArrayIterator end();

//        template<typename T1>
//        friend std::ostream &operator<<(std::ostream &out, const Array<T1> &arr);
    };

    template<typename T>
    Array<T>::Array() {
        this->data = nullptr;
        this->size = 0;
    }

    template<typename T>
    Array<T>::Array(unsigned int size) {
        this->data = new ArrayElement<T>[size];
        this->size = size;
    }

    template<typename T>
    void Array<T>::append(T value) {
        if (this->size == 0) {
            this->data = new ArrayElement<T>[1];
            this->data[this->size] = value;
        } else {
            Array<T> buffArr(*this);
            delete[] this->data;
            this->data = new ArrayElement<T>[this->size + 1];
            for (unsigned int i = 0; i < this->size; ++i) {
                this->data[i] = *buffArr[i];
            }
            this->data[this->size] = value;
        }
        ++this->size;
    }

    template<typename T>
    ArrayElement<T> *Array<T>::operator[](unsigned int index) {
        if (index >= 0 && index < this->size) {
            return &this->data[index];
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    Array<T>::Array(const Array<T> &arr) {
        this->data = new ArrayElement<T>[arr.size];
        for (int i = 0; i < arr.size; ++i) {
            this->data[i] = arr.data[i];
        }
        this->size = arr.size;
    }

    template<typename T>
    Array<T>::~Array() = default;

//    template<typename T1>
//    std::ostream &operator<<(std::ostream &out, const Array<T1> &arr) {
//        if (arr.size != 0) {
//            out << "[";
//            for (int i = 0; i < arr.size; ++i) {
//                if (i == arr.size - 1) {
//                    out << arr.data[i] << "]";
//                } else {
//                    out << arr.data[i] << ", ";
//                }
//            }
//        } else {
//            out << "[]";
//        }
//        return out;
//    }

    template<typename T>
    Array<T>::Array(T *mas, unsigned int size) {
        this->data = new ArrayElement<T>[size];
        for (unsigned int i = 0; i < size; ++i) {
            this->data[i] = mas[i];
        }
        this->size = size;
    }

    template<typename T>
    void Array<T>::prepend(T value) {
        if (this->size == 0) {
            this->data = new ArrayElement<T>[1];
            this->data[this->size] = value;
        } else {
            Array<T> buffArr(*this);
            delete[] this->data;
            this->data = new ArrayElement<T>[this->size + 1];
            for (unsigned int i = 1; i < this->size + 1; ++i) {
                this->data[i] = *buffArr[i - 1];
            }
            this->data[0] = value;
        }
        ++this->size;
    }

    template<typename T>
    void Array<T>::pop(unsigned int index) {
        if (index >= 0 && index < this->size) {
            Array<T> buffArr(*this);
            delete[] this->data;
            this->size = buffArr.length() - 1;
            this->data = new ArrayElement<T>[this->size];
            for (unsigned int i = 0; i < buffArr.length(); ++i) {
                if (i < index) {
                    this->data[i] = *buffArr[i];
                } else if (i > index) {
                    this->data[i - 1] = *buffArr[i];
                }
            }
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    unsigned int Array<T>::length() {
        return this->size;
    }

    template<typename T>
    void Array<T>::remove() {
        while (this->size > 0) {
            this->pop(0);
        }
    }

    template<typename T>
    void Array<T>::swap(unsigned int index1, unsigned int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size) {
            T buff = this->data[index1];
            this->data[index1] = this->data[index2];
            this->data[index2] = buff;
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    T &Array<T>::getElement(unsigned int index) {
        if (index >= 0 && index < this->size) {
            return this->data[index].getValue();
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    int Array<T>::getIndex(T value) {
        for (unsigned int i = 0; i < this->size; ++i) {
            if (this->data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    void Array<T>::resize(unsigned int size) {
        if (size > this->size) {
            Array<T> buffArr(*this);
            delete[] this->data;
            this->data = new ArrayElement<T>[size];
            for (unsigned int i = 0; i < this->size; ++i) {
                this->data[i] = *buffArr[i];
            }
            this->size = size;
        } else {
            throw exceptions::ArrayException("Array can't resize!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    ArrayElement<T> *Array<T>::getFirst() {
        if (this->size != 0) {
            return &this->data[0];
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    ArrayElement<T> *Array<T>::getLast() {
        if (this->size != 0) {
            return &this->data[this->size - 1];
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    void Array<T>::insert(unsigned int index, T value) {
        if (index >= 0 && index <= this->size) {
            Array<T> buffArr(*this);
            delete[] this->data;
            ++this->size;
            this->data = new ArrayElement<T>[this->size];
            for (unsigned int i = 0; i < this->size; ++i) {
                if (i < index) {
                    this->data[i] = *buffArr[i];
                } else if (i == index) {
                    this->data[i] = value;
                } else if (i > index) {
                    this->data[i] = *buffArr[i - 1];
                }
            }
        } else {
            throw exceptions::ArrayException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    Array<T> &Array<T>::operator=(const Array<T> &arr) {
        if (this == &arr) {
            return *this;
        }
        this->size = arr.size;
        delete[] this->data;
        this->data = new ArrayElement<T>[this->size];
        for (int i = 0; i < this->size; ++i) {
            this->data[i] = arr.data[i];
        }
        return *this;
    }

    template<typename T>
    Array<T> Array<T>::operator+(const Array<T> &arr) {
        Array<T> buffArr(*this);
        for (unsigned int i = 0; i < arr.size; ++i) {
            buffArr.append(arr.data[i]);
        }
        return buffArr;
    }

    template<typename T>
    Array<T> Array<T>::operator*(unsigned int c) {
        if (c == 0) {
            this->remove();
            return *this;
        } else {
            Array<T> buffArr(*this);
            Array<T> arr;
            for (unsigned int i = 0; i < c; ++i) {
                arr = arr + buffArr;
            }
            return arr;
        }
    }

    template<typename T>
    bool Array<T>::operator==(const Array<T> &arr) {
        if (this->size == arr.size) {
            for (unsigned int i = 0; i < this->size; ++i) {
                if (this->data[i] != arr.data[i]) {
                    return false;
                }
            }
            return true;
        } else {
            throw exceptions::ArrayException("It is not possible to compare arrays of different lengths!", __LINE__,
                                             __FILE__);
        }
    }

    template<typename T>
    typename Array<T>::ArrayIterator Array<T>::begin() {
        return &(this->data[0]);
    }

    template<typename T>
    typename Array<T>::ArrayIterator Array<T>::end() {
        return &(this->data[this->size]);
    }
}
#endif
