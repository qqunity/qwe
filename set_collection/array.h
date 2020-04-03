#ifndef SET_COLLECTION_ARRAY_H
#define SET_COLLECTION_ARRAY_H

    #include "array_element.h"
    #include <string>

    template <typename T>
    class Array{
        private:
            ArrayElement<T> *data;
            int count;
        public:
            Array();
            Array(int);
            Array(const Array<T> &);
            ~Array();
            void append(T);
            void prepend(T);
            void pop(int);
            void del();
            void swap(int, int);
            Array<T> reversed();
            T get_element(int);
            ArrayElement<T> *get_element_ptr(int);
            int get_index(T);
            void resize(int);
            T get_first();
            T get_last();
            void insert(int, T);
            void set_element(int, T);
            void print_array();
            Array<T> &operator = (const Array<T> &);
            Array<T> operator + (const Array<T> &);
            bool operator == (const Array<T> &);
            bool operator != (const Array<T> &);
            T operator [] (int);
            Array<T> operator * (int);
            int length();
            class ArrIterator {
            private:
                ArrayElement<T> *cur_o;
            public:
                ArrIterator(ArrayElement<T> *);
                ArrayElement<T> &operator + (int );
                ArrayElement<T> &operator - (int );
                ArrayElement<T> &operator ++ (int);
                ArrayElement<T> &operator -- (int);
                ArrayElement<T> &operator ++ ();
                ArrayElement<T> &operator -- ();
                ArrayElement<T> &operator = (ArrayElement<T> &);
                bool operator != (const ArrIterator &);
                bool operator == (const ArrIterator &);
                ArrayElement<T> &operator * ();
            };
            ArrIterator begin();
            ArrIterator end();
            template<typename T1> friend std::ostream& operator<< (std::ostream &, const Array<T1> &);
    };

    template<typename T>
    Array<T>::ArrIterator::ArrIterator(ArrayElement<T> *first_o) {
        this->cur_o = first_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator+(int n) {
        return *(this->cur_o + n);
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator-(int n) {
        return *(this->cur_o - n);
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator++(int) {
        return *this->cur_o++;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator--(int) {
        return *this->cur_o--;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator++() {
        return *++this->cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator--() {
        return *--this->cur_o;
    }

    template<typename T>
    bool Array<T>::ArrIterator::operator!=(const Array::ArrIterator &It) {
        return this->cur_o != It.cur_o;
    }

    template<typename T>
    bool Array<T>::ArrIterator::operator==(const Array::ArrIterator &It) {
        return this->cur_o == It.cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator*() {
        return *this->cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator=(ArrayElement<T> &It) {
        this->cur_o = &It;
        return *this->cur_o;
    }

    template<typename T>
    Array<T>::Array() {
        this->data = nullptr;
        this->count = 0;
    }

    template<typename T>
    Array<T>::Array(const Array<T> &Arr) {
        int n = Arr.count;
        this->data = new ArrayElement<T>[n];
        this->count = 0;
        for (int i = 0; i < n; ++i){
            this->data[i].set_value((Arr.data[i]).get_data());
            ++this->count;
        }
    }

    template<typename T>
    void Array<T>::append(T val) {
        ArrayElement<T> buff;
        buff.set_value(val);
        if (count == 0){
            this->data = new ArrayElement<T>[1];
            this->data[0] = buff;
            ++this->count;
        }
        else {
            Array<T> arr_buff(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[count + 1];
            for (int i = 0; i < count; ++i){
                this->data[i].set_value(arr_buff.get_element(i));
            }
            this->data[count] = buff;
            ++this->count;
        }
    }

    template<typename T>
    T Array<T>::get_element(int index) {
        return this->data[index].get_data();
    }

    template<typename T>
    void Array<T>::print_array() {
        if (this->count != 0) {
            std::cout << "[";
            for (int i = 0; i < this->count; ++i) {
                if (i == this->count - 1) {
                    std::cout << this->data[i].get_data();
                } else {
                    std::cout << this->data[i].get_data() << ", ";
                }
            }
            std::cout << "]" << std::endl;
        }
        else {
            std::cout << "null";
        }
    }

    template<typename T>
    void Array<T>::prepend(T val) {
        ArrayElement<T> buff;
        buff.set_value(val);
        if (count == 0){
            this->data = new ArrayElement<T>[1];
            this->data[0] = buff;
            ++this->count;
        }
        else {
            Array<T> arr_buff(*this);
            delete [] this->data;
            this->data = new ArrayElement<T>[count + 1];
            for (int i = 1; i < count + 1; ++i){
                this->data[i].set_value(arr_buff.get_element(i - 1));
            }
            this->data[0] = buff;
            ++this->count;
        }
    }

    template<typename T>
    void Array<T>::pop(int index) {
        Array<T> buff;
        for (int i = 0; i < count; ++i){
            if (i != index) {
                buff.append(data[i].get_data());
            }
        }
        delete [] this->data;
        this->data = new ArrayElement<T>[count - 1];
        --this->count;
        for (int i = 0; i < count; ++i){
            this->data[i].set_value(buff.get_element(i));
        }
    }

    template<typename T>
    void Array<T>::del() {
        while (count != 0){
            pop(0);
        }
    }

    template<typename T>
    Array<T>::~Array() = default;

    template<typename T>
    void Array<T>::swap(int index1, int index2) {
        T buff_t = this->data[index1].get_data();
        this->data[index1].set_value(data[index2].get_data());
        this->data[index2].set_value(buff_t);
    }

    template<typename T>
    Array<T> Array<T>::reversed() {
        Array<T> buff;
        for (int i = count - 1; i >=0; --i){
            buff.append(data[i].get_data());
        }
        return buff;
    }

    template<typename T>
    Array<T> &Array<T>::operator=(const Array<T> &Arr) {
        if (this == &Arr){
            return *this;
        }
        this->~Array<T>();
        this->count = Arr.count;
        this->data = new ArrayElement<T>[count];
        for(int i = 0; i < count; ++i){
            this->data[i].set_value(Arr.data[i].get_data());
        }
        return *this;
    }

    template<typename T>
    int Array<T>::length() {
        return this->count;
    }

    template<typename T>
    T Array<T>::get_first() {
        return this->data[0].get_data();
    }

    template<typename T>
    T Array<T>::get_last() {
        return this->data[count - 1].get_data();
    }

    template<typename T>
    void Array<T>::set_element(int index, T val) {
        this->data[index].set_value(val);
    }

    template<typename T>
    void Array<T>::insert(int index, T value) {
        auto buff = new ArrayElement<T>[count + 1];
        for (int i = 0; i < count + 1; ++i){
            if (i < index){
                buff[i].set_value(data[i].get_data());
            }
            else if (i == index){
                buff[i].set_value(value);
            }
            else {
                buff[i].set_value(data[i - 1].get_data());
            }
        }
        delete [] this->data;
        ++this->count;
        this->data = new ArrayElement<T>[count];
        for (int i = 0; i < count; ++i){
            this->data[i].set_value(buff[i].get_data());
        }
    }

    template<typename T>
    Array<T> Array<T>::operator+(const Array<T> &Arr) {
        Array<T> buff (*this);
        for (int i = 0; i < Arr.count; ++i){
            buff.append(Arr.data[i].get_data());
        }
        return buff;
    }

    template<typename T>
    bool Array<T>::operator==(const Array<T> &Arr) {
        if (this->count != Arr.count){
            return false;
        }
        for (int i = 0; i < this->count; ++i){
            if (this->data[i].get_data() != Arr.data[i].get_data()){
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool Array<T>::operator!=(const Array<T> &Arr) {
        return !(*this == Arr);
    }

    template<typename T>
    Array<T> Array<T>::operator*(int k) {
        if (k == 0){
            this->del();
            return *this;
        }
        else {
            Array<T> buff;
            for (int j = 0; j < k; ++j){
                for (int i = 0; i < this->count; ++i){
                    buff.append(this->data[i].get_data());
                }
            }
            return buff;
        }
    }

    template<typename T>
    int Array<T>::get_index(T val) {
        for (int i = 0; i < count; ++i){
            if (this->data[i].get_data() == val){
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    T Array<T>::operator[](int index) {
        return this->data[index].get_data();
    }

    template<typename T>
    typename Array<T>::ArrIterator Array<T>::begin() {
        return this->data;
    }

    template<typename T>
    typename Array<T>::ArrIterator Array<T>::end() {
        return this->data + this->count;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const Array<T1> &Arr) {
        if (Arr.count != 0) {
            out << "[";
            for (int i = 0; i < Arr.count; ++i) {
                if (i == Arr.count - 1) {
                    out << Arr.data[i].get_data();
                } else {
                    out << Arr.data[i].get_data() << ", ";
                }
            }
            out << "]";
        }
        else {
            out << "null";
        }
        return out;
    }

    template<typename T>
    ArrayElement<T> *Array<T>::get_element_ptr(int index) {
        return &this->data[index];
    }

    template<typename T>
    Array<T>::Array(int n) {
        this->count = n;
        this->data = new ArrayElement<T>[n];
    }

    template<typename T>
    void Array<T>::resize(int n) {
        if (this->count == 0){
            this->count = n;
            this->data = new ArrayElement<T>[n];
        }
        else {
            auto buff = new ArrayElement<T>[this->count];
            for (int i = 0; i < this->count; ++i){
                buff[i].set_value(this->data[i].get_data());
            }
            if (n < this->count){
                std::cout << "Invalid resize...";
            }
            else {
                delete [] data;
                this->data = new ArrayElement<T>[n];
                for (int i = 0; i < this->count; ++i){
                    this->data[i].set_value(buff[i].get_data());
                }
                this->count = n;
            }
        }
    }

#endif
