#ifndef COLLECTIONS_ARRAY_H
#define COLLECTIONS_ARRAY_H

    #include "ArrayElement.h"

    template<typename T>
    class Array{
        private:
            ArrayElement<T> *data;
            int size;
        public:
            Array();
            Array(T *, int);
            Array(int);
            Array(const Array<T> &);
            void append(T);
            void prepend(T);
            void pop(int);
            void remove();
            void swap(int, int);
            T getElement(int);
            int getIndex(T);
            void resize(int);
            int length();
            T getFirst();
            T getLast();
            void insert(int, T);
            Array<T> &operator = (const Array<T> &);
            Array<T> operator + (const Array<T> &);
            Array<T> operator * (int);
            ArrayElement<T> &operator [] (int);
            bool operator == (const Array<T> &);
            bool operator != (const Array<T> &);
            ~Array();
            class ArrayIterator {
                private:
                    ArrayElement<T> *curObj;
                public:
                    ArrayIterator(ArrayElement<T> *obj) {
                        this->curObj = obj;
                    }
                    ArrayElement<T> &operator + (int k) {
                        return *(this->curObj + k);
                    }
                    ArrayElement<T> &operator - (int k) {
                        return *(this->curObj - k);
                    }
                    ArrayElement<T> &operator ++ (int) {
                        return *this->curObj++;
                    }
                    ArrayElement<T> &operator -- (int) {
                        return *this->curObj--;
                    }
                    ArrayElement<T> &operator ++ () {
                        return *++this->curObj;
                    }
                    ArrayElement<T> &operator -- () {
                        return *--this->curObj;
                    }
                    ArrayElement<T> &operator = (ArrayElement<T> &ArrEl) {
                        this->curObj = &ArrEl;
                        return *(this->curObj);
                    }
                    bool operator != (const ArrayIterator &ArrIt) {
                        return this->curObj != ArrIt.curObj;
                    }
                    bool operator == (const  ArrayIterator &ArrIt) {
                        return this->curObj == ArrIt.curObj;
                    }
                    ArrayElement<T> &operator * () {
                        return *this->curObj;
                    }
            };
            ArrayIterator begin();
            ArrayIterator end();
            template<typename T1> friend std::ostream& operator<< (std::ostream &, const Array<T1> &);
    };

    template<typename T>
    Array<T>::Array() {
        this->data = nullptr;
        this->size = 0;
    }

    template<typename T>
    Array<T>::Array(int n) {
        this->data = new ArrayElement<T>[n];
        this->size = n;
    }

    template<typename T>
    Array<T>::Array(const Array<T> &Arr) {
        this->data = new ArrayElement<T>[Arr.size];
        for (int i = 0; i < Arr.size; ++i){
            this->data[i] = Arr.data[i];
        }
        this->size = Arr.size;
    }

    template<typename T>
    void Array<T>::append(T val) {
        if (this->size == 0){
            this->data = new ArrayElement<T>[1];
            this->data[0] = val;
            ++this->size;
        }
        else {
            Array<T> BuffArr(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[this->size + 1];
            for (int i = 0; i < this->size; ++i){
                this->data[i] = BuffArr[i];
            }
            this->data[this->size] = val;
            ++this->size;
        }
    }

    template<typename T>
    ArrayElement<T> &Array<T>::operator[](int index) {
        if (index >= 0 && index < this->size){
            return this->data[index];
        }
        else {
            throw arrayException::ArrayException("Index out of range!");
        }
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const Array<T1> &Arr) {
        if (Arr.size != 0) {
            out << "[";
            for (int i = 0; i < Arr.size; ++i) {
                if (i == Arr.size - 1) {
                    out << Arr.data[i] << "]";
                } else {
                    out << Arr.data[i] << ", ";
                }
            }
            return out;
        }
        else {
            out << "NULL";
        }
    }

    template<typename T>
    void Array<T>::prepend(T val) {
        if (this->size == 0){
            this->data = new ArrayElement<T>[1];
            this->data[0] = val;
            ++this->size;
        }
        else {
            Array<T> BuffArr(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[this->size + 1];
            for (int i = 1; i < this->size + 1; ++i){
                this->data[i] = BuffArr[i - 1];
            }
            this->data[0] = val;
            ++this->size;
        }
    }

    template<typename T>
    void Array<T>::pop(int index) {
        if (index >= 0 && index < this->size){
            Array<T> BuffArr(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[this->size - 1];
            for (int i = 0; i < this->size; ++i){
                if (i < index) {
                    this->data[i] =  BuffArr[i];
                }
                else if (i > index) {
                    this->data[i - 1] = BuffArr[i];
                }
            }
            --this->size;
        }
        else {
            throw arrayException::ArrayException("Index out of range!");
        }
    }

    template<typename T>
    void Array<T>::remove() {
        while (this->size > 0){
            pop(0);
        }
    }

    template<typename T>
    void Array<T>::swap(int index1, int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size){
            T buffEl = this->data[index1];
            this->data[index1] = this->data[index2];
            this->data[index2] = buffEl;
        }
        else {
            throw arrayException::ArrayException("Index out of range!");
        }
    }

    template<typename T>
    T Array<T>::getElement(int index) {
        if (index >= 0 && index < this->size){
            return this->data[index];
        }
        else {
            throw arrayException::ArrayException("Index out of range!");
        }
    }

    template<typename T>
    int Array<T>::getIndex(T val) {
        for (int i = 0; i < this->size; ++i){
            if (this->data[i] == val){
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    void Array<T>::resize(int n) {
        if (n >= this->size){
            Array<T> BuffArr(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[n];
            for (int i = 0; i < this->size; ++i){
                this->data[i] = BuffArr[i];
            }
            this->size = n;
        }
        else {
            throw arrayException::ArrayException("Array can't resize!");
        }
    }

    template<typename T>
    int Array<T>::length() {
        return this->size;
    }

    template<typename T>
    T Array<T>::getFirst() {
        return this->data[0];
    }

    template<typename T>
    T Array<T>::getLast() {
        return this->data[this->size - 1];
    }

    template<typename T>
    void Array<T>::insert(int index, T val) {
        if (index >= 0 && index <= this->size){
            Array<T> BuffArr(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[this->size + 1];
            for (int i = 0; i < this->size + 1; ++i){
                if (i < index){
                    this->data[i] = BuffArr[i];
                }
                else if (i == index){
                    this->data[i] = val;
                }
                else if (i > index){
                    this->data[i] = BuffArr[i - 1];
                }
            }
            ++this->size;
        }
        else {
            throw arrayException::ArrayException("Index out of range!");
        }
    }

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &Arr) {
    if (this == &Arr){
        return *this;
    }
    this->size = Arr.size;
    delete [] this->data;
    this->data = new ArrayElement<T>[this->size];
    for(int i = 0; i < this->size; ++i){
        this->data[i] = Arr.data[i];
    }
    return *this;
}

    template<typename T>
    Array<T> Array<T>::operator+(const Array<T> &Arr) {
        Array<T> BuffArr(*this);
        for (int i = 0; i < Arr.size; ++i){
            BuffArr.append(Arr.data[i]);
        }
        return BuffArr;
    }

    template<typename T>
    Array<T> Array<T>::operator*(int k) {
        if (k == 0){
            remove();
            return *this;
        }
        else {
            Array<T> BuffArr(*this);
            for (int i = 1; i < k; ++i){
                BuffArr = BuffArr + *this;
            }
            return BuffArr;
        }
    }

    template<typename T>
    bool Array<T>::operator==(const Array<T> &Arr) {
        if (this->size == Arr.size){
            for (int i = 0; i < this->size; ++i){
                if (this->data[i] != Arr.data[i]){
                    return false;
                }
            }
            return true;
        }
        else {
            throw arrayException::ArrayException("It is not possible to compare arrays of different lengths!");
        }
    }

    template<typename T>
    bool Array<T>::operator!=(const Array<T> &Arr) {
        return !(*this == Arr);
    }

    template<typename T>
    typename Array<T>::ArrayIterator Array<T>::end() {
        return &this->data[this->size];
    }

    template<typename T>
    typename Array<T>::ArrayIterator Array<T>::begin() {
        return &this->data[0];
    }

    template<typename T>
    Array<T>::Array(T *mas, int n) {
        this->size = n;
        this->data = new ArrayElement<T>[this->size];
        for (int i = 0; i < this->size; ++i) {
            this->data[i] = mas[i];
        }
    }

template<typename T>
    Array<T>::~Array() = default;

#endif
