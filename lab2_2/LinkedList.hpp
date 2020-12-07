#ifndef SORTER_LINKEDLIST_HPP
#define SORTER_LINKEDLIST_HPP

#include "ListElement.hpp"
#include "Exceptions.hpp"

namespace list {
    template<typename T>
    class LinkedList {
    private:
        ListElement<T> *headPtr;
        ListElement<T> *tailPtr;
        unsigned int size;
    public:
        LinkedList();

        LinkedList(T *mas, unsigned int size);

        LinkedList(const LinkedList<T> &list);

        void append(T value);

        void prepend(T value);

        void pop(unsigned int index);

        void remove();

        void swap(unsigned int index1, unsigned int index2);

        T &getElement(unsigned int index);

        int getIndex(T value);

        unsigned int length();

        ListElement<T> *getFirst();

        ListElement<T> *getLast();

        void insert(unsigned int index, T value);

        LinkedList<T> &operator=(const LinkedList<T> &list);

        LinkedList<T> operator+(const LinkedList<T> &list);

        LinkedList<T> operator*(unsigned int k);

        ListElement<T> *operator[](unsigned int index);

        bool operator==(const LinkedList<T> &list);

//        template<typename T1>
//        friend std::ostream &operator<<(std::ostream &out, const LinkedList<T1> &list);

        class LinkedListIterator {
        private:
            ListElement<T> *curObj;
        public:
            LinkedListIterator(ListElement<T> *obj) {
                this->curObj = obj;
            }

            ListElement<T> &operator+(int k) {
                auto buffObj = curObj;
                for (int i = 0; i < k && buffObj != nullptr; ++i) {
                    buffObj = buffObj->getNextPtr();
                }
                return *buffObj;
            }

            ListElement<T> &operator-(int k) {
                auto buffObj = curObj;
                for (int i = 0; i < k && buffObj != nullptr; ++i) {
                    buffObj = buffObj->getPrevPtr();
                }
                return *buffObj;
            }

            int operator-(const LinkedListIterator &listIt) {
                int i = 0;
                LinkedListIterator buffIt = listIt;
                while (buffIt != *this) {
                    ++i;
                    ++buffIt;
                }
                return i;
            }

            ListElement<T> &operator++(int) {
                this->curObj = this->curObj->getNextPtr();
                return *(this->curObj->getPrevPtr());
            }

            ListElement<T> &operator--(int) {
                this->curObj = this->curObj->getPrevPtr();
                return *(this->curObj->getNextPtr());
            }

            ListElement<T> &operator++() {
                this->curObj = this->curObj->getNextPtr();
                return *this->curObj;
            }

            ListElement<T> &operator--() {
                this->curObj = this->curObj->getPrevPtr();
                return *this->curObj;
            }

            LinkedListIterator &operator=(ListElement<T> &listEl) {
                this->curObj = &listEl;
                return *this;
            }

            bool operator==(const LinkedListIterator &listIt) {
                return this->curObj == listIt.curObj;
            }

            ListElement<T> &operator*() {
                return *this->curObj;
            }
        };

        LinkedListIterator begin();

        LinkedListIterator end();

        ~LinkedList();
    };

    template<typename T>
    LinkedList<T>::LinkedList() {
        this->headPtr = nullptr;
        this->tailPtr = nullptr;
        this->size = 0;
    }

    template<typename T>
    void LinkedList<T>::append(T value) {
        if (this->size == 0) {
            this->headPtr = new ListElement<T>(value);
            this->tailPtr = this->headPtr;
        } else {
            this->tailPtr->setNextPtr(new ListElement<T>(value));
            this->tailPtr->getNextPtr()->setPrevPtr(this->tailPtr);
            this->tailPtr = this->tailPtr->getNextPtr();
        }
        ++this->size;
    }

//    template<typename T1>
//    std::ostream &operator<<(std::ostream &out, const LinkedList<T1> &list) {
//        if (list.size != 0) {
//            auto buffPtr = list.headPtr;
//            out << "[";
//            unsigned int i = 0;
//            while (buffPtr != nullptr) {
//                if (i != list.size - 1) {
//                    out << buffPtr->getValue() << ", ";
//                } else {
//                    out << buffPtr->getValue() << "]";
//                }
//                ++i;
//                buffPtr = buffPtr->getNextPtr();
//            }
//        } else {
//            out << "[]";
//        }
//        return out;
//    }

    template<typename T>
    LinkedList<T>::LinkedList(T *mas, unsigned int size) {
        for (unsigned int i = 0; i < size; ++i) {
            this->append(mas[i]);
        }
    }

    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList<T> &list) {
        this->headPtr = nullptr;
        this->tailPtr = nullptr;
        this->size = 0;
        auto buffPtr = list.headPtr;
        while (buffPtr != nullptr) {
            this->append(buffPtr->getValue());
            buffPtr = buffPtr->getNextPtr();
        }
    }

    template<typename T>
    void LinkedList<T>::prepend(T value) {
        if (this->size == 0) {
            this->headPtr = new ListElement<T>(value);
            this->tailPtr = this->headPtr;
        } else {
            this->headPtr->setPrevPtr(new ListElement<T>(value));
            this->headPtr->getPrevPtr()->setNextPtr(this->headPtr);
            this->headPtr = this->headPtr->getPrevPtr();
        }
        ++this->size;
    }

    template<typename T>
    void LinkedList<T>::pop(unsigned int index) {
        if (index >= 0 && index < this->size) {
            if (index != 0 && index != this->size - 1 && this->size != 1) {
                auto buffPtr = this->headPtr;
                unsigned int i = 0;
                while (i < index - 1) {
                    buffPtr = buffPtr->getNextPtr();
                    ++i;
                }
                auto buffRemPtr = buffPtr->getNextPtr();
                buffPtr->setNextPtr(buffPtr->getNextPtr()->getNextPtr());
                buffPtr->getNextPtr()->setPrevPtr(buffRemPtr->getPrevPtr());
                delete buffRemPtr;
            } else if (index == 0 && this->size != 1) {
                this->headPtr = this->headPtr->getNextPtr();
                delete this->headPtr->getPrevPtr();
                this->headPtr->setPrevPtr(nullptr);
            } else if (index == this->size - 1 && this->size != 1) {
                this->tailPtr = this->tailPtr->getPrevPtr();
                delete this->tailPtr->getNextPtr();
                this->tailPtr->setNextPtr(nullptr);
            } else if (this->size == 1) {
                delete this->headPtr;
                this->headPtr = nullptr;
                this->tailPtr = nullptr;
            }
            --this->size;
        } else {
            throw exceptions::LinkedListException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    void LinkedList<T>::remove() {
        while (this->size != 0) {
            this->pop(0);
        }
    }

    template<typename T>
    void LinkedList<T>::swap(unsigned int index1, unsigned int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size) {
            auto buffPtr1 = this->headPtr;
            auto buffPtr2 = this->headPtr;
            for (unsigned int i = 0; i < index1; ++i) {
                buffPtr1 = buffPtr1->getNextPtr();
            }
            for (unsigned int i = 0; i < index2; ++i) {
                buffPtr2 = buffPtr2->getNextPtr();
            }
            auto buff = buffPtr1->getValue();
            buffPtr1->setValue(buffPtr2->getValue());
            buffPtr2->setValue(buff);
        } else {
            throw exceptions::LinkedListException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    T &LinkedList<T>::getElement(unsigned int index) {
        if (index >= 0 && index < this->size) {
            auto buffPtr = this->headPtr;
            for (unsigned int i = 0; i < index; ++i) {
                buffPtr = buffPtr->getNextPtr();
            }
            return buffPtr->getValue();
        } else {
            throw exceptions::LinkedListException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    int LinkedList<T>::getIndex(T value) {
        auto buffPtr = this->headPtr;
        unsigned int i = 0;
        while (buffPtr != nullptr) {
            if (buffPtr->getValue() == value) {
                return i;
            }
            ++i;
            buffPtr = buffPtr->getNextPtr();
        }
        return -1;
    }

    template<typename T>
    unsigned int LinkedList<T>::length() {
        return this->size;
    }

    template<typename T>
    ListElement<T> *LinkedList<T>::getFirst() {
        return this->headPtr;
    }

    template<typename T>
    ListElement<T> *LinkedList<T>::getLast() {
        return this->tailPtr;
    }

    template<typename T>
    void LinkedList<T>::insert(unsigned int index, T value) {
        if (index >= 0 && index <= this->size) {
            if (index != 0 && index != this->size) {
                auto buffPtr = this->headPtr;
                for (unsigned int i = 0; i < index - 1; ++i) {
                    buffPtr = buffPtr->getNextPtr();
                }
                auto newPtr = new ListElement<T>(value);
                newPtr->setPrevPtr(buffPtr);
                newPtr->setNextPtr(buffPtr->getNextPtr());
                buffPtr->setNextPtr(newPtr);
                newPtr->getNextPtr()->setPrevPtr(newPtr);
                ++this->size;
            } else if (index == 0) {
                this->prepend(value);
            } else if (index == this->size) {
                this->append(value);
            }
        } else {
            throw exceptions::LinkedListException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        this->remove();
        auto buffPtr = list.headPtr;
        while (buffPtr != nullptr) {
            this->append(buffPtr->getValue());
            buffPtr = buffPtr->getNextPtr();
        }
        return *this;
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::operator+(const LinkedList<T> &list) {
        LinkedList<T> buffList(*this);
        auto buffPtr = list.headPtr;
        while (buffPtr != nullptr) {
            buffList.append(buffPtr->getValue());
            buffPtr = buffPtr->getNextPtr();
        }
        return buffList;
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::operator*(unsigned int k) {
        if (k == 0) {
            this->remove();
            return *this;
        } else {
            LinkedList<T> buffList;
            LinkedList<T> buff(*this);
            for (unsigned int i = 0; i < k; ++i) {
                buffList = buffList + buff;
            }
            return buffList;
        }
    }

    template<typename T>
    ListElement<T> *LinkedList<T>::operator[](unsigned int index) {
        if (index >= 0 && index < this->size) {
            auto buffPtr = this->headPtr;
            for (unsigned int i = 0; i < index; ++i) {
                buffPtr = buffPtr->getNextPtr();
            }
            return buffPtr;
        } else {
            throw exceptions::LinkedListException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    bool LinkedList<T>::operator==(const LinkedList<T> &list) {
        if (this->size == list.size) {
            auto buffPtr1 = this->headPtr;
            auto buffPtr2 = list.headPtr;
            while (buffPtr1 != nullptr && buffPtr2 != nullptr) {
                if (buffPtr1->getValue() != buffPtr2->getValue()) {
                    return false;
                }
                buffPtr1 = buffPtr1->getNextPtr();
                buffPtr2 = buffPtr2->getNextPtr();
            }
            return true;
        } else {
            throw exceptions::LinkedListException("It is not possible to compare list of different lengths!", __LINE__,
                                                  __FILE__);
        }
    }

    template<typename T>
    typename LinkedList<T>::LinkedListIterator LinkedList<T>::end() {
        return this->tailPtr->getNextPtr();
    }

    template<typename T>
    typename LinkedList<T>::LinkedListIterator LinkedList<T>::begin() {
        return this->headPtr;
    }

    template<typename T>
    LinkedList<T>::~LinkedList() = default;
}

#endif
