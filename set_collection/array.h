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
        Array(const Array<T>&);
        ~Array();
        void append(T);
        void prepend(T);
        void pop(int);
        void del();
        void swap(int, int);
        Array<T> reversed();
        T get_element(int);
        int get_index(T);
        T get_first();
        T get_last();
        void insert(int, T);
        void set_element(int, T);
        void print_array();
//        void sorted(const std::string&);
        Array<T> &operator = (const Array<T>&);
        Array<T> operator + (const Array<T>&);
        bool operator == (const Array<T>&);
        bool operator != (const Array<T>&);
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
            ArrayElement<T> &operator = (ArrayElement<T>&);
            bool operator != (const ArrIterator&);
            bool operator == (const ArrIterator&);
            ArrayElement<T> &operator * ();
        };
        ArrIterator begin();
        ArrIterator end();
    };

    template<typename T>
    Array<T>::ArrIterator::ArrIterator(ArrayElement<T> *first_o) {
        cur_o = first_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator+(int n) {
        return *(cur_o + n);
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator-(int n) {
        return *(cur_o - n);
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator++(int) {
        return *cur_o++;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator--(int) {
        return *cur_o--;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator++() {
        return *++cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator--() {
        return *--cur_o;
    }

    template<typename T>
    bool Array<T>::ArrIterator::operator!=(const Array::ArrIterator &It) {
        return cur_o != It.cur_o;
    }

    template<typename T>
    bool Array<T>::ArrIterator::operator==(const Array::ArrIterator &It) {
        return cur_o == It.cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator*() {
        return *cur_o;
    }

    template<typename T>
    ArrayElement<T> &Array<T>::ArrIterator::operator=(ArrayElement<T> &It) {
        cur_o = &It;
        return *cur_o;
    }

template<typename T>
    Array<T>::Array() {
        data = nullptr;
        count = 0;
    }

    template<typename T>
    Array<T>::Array(const Array<T> &Arr) {
        int n = Arr.count;
        data = new ArrayElement<T>[n];
        count = 0;
        for (int i = 0; i < n; ++i){
            data[i].set_value((Arr.data[i]).get_value());
            ++count;
        }
    }

    template<typename T>
    void Array<T>::append(T val) {
        ArrayElement<T> buff;
        buff.set_value(val);
        if (count == 0){
            data = new ArrayElement<T>[1];
            data[0] = buff;
            ++count;
        }
        else {
            Array<T> arr_buff(*this);
            data = new ArrayElement<T>[count + 1];
            for (int i = 0; i < count; ++i){
                data[i].set_value(arr_buff.get_element(i));
            }
            data[count] = buff;
            ++count;
        }
    }

    template<typename T>
    T Array<T>::get_element(int index) {
        return data[index].get_value();
    }

    template<typename T>
    void Array<T>::print_array() {
        if (count != 0) {
            std::cout << "[";
            for (int i = 0; i < count; ++i) {
                if (i == count - 1) {
                    std::cout << data[i].get_value();
                } else {
                    std::cout << data[i].get_value() << ", ";
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
            data = new ArrayElement<T>[1];
            data[0] = buff;
            ++count;
        }
        else {
            Array<T> arr_buff(*this);
            data = new ArrayElement<T>[count + 1];
            for (int i = 1; i < count + 1; ++i){
                data[i].set_value(arr_buff.get_element(i - 1));
            }
            data[0] = buff;
            ++count;
        }
    }

    template<typename T>
    void Array<T>::pop(int index) {
        Array<T> buff;
        for (int i = 0; i < count; ++i){
            if (i != index) {
                buff.append(data[i].get_value());
            }
        }
        delete [] data;
        data = new ArrayElement<T>[count - 1];
        --count;
        for (int i = 0; i < count; ++i){
            data[i].set_value(buff.get_element(i));
        }
    }

    template<typename T>
    void Array<T>::del() {
        while (count != 0){
            pop(0);
        }
    }

template<typename T>
    Array<T>::~Array() {
        del();
    }

    template<typename T>
    void Array<T>::swap(int index1, int index2) {
        T buff_t = data[index1].get_value();
        data[index1].set_value(data[index2].get_value());
        data[index2].set_value(buff_t);
    }

    template<typename T>
    Array<T> Array<T>::reversed() {
        Array<T> buff;
        for (int i = count - 1; i >=0; --i){
            buff.append(data[i].get_value());
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
        this->data = new ArrayElement<int>[count];
        for(int i = 0; i < count; ++i){
            this->data[i].set_value(Arr.data[i].get_value());
        }
        return *this;
    }

    template<typename T>
    int Array<T>::length() {
        return count;
    }

    template<typename T>
    T Array<T>::get_first() {
        return data[0].get_value();
    }

    template<typename T>
    T Array<T>::get_last() {
        return data[count - 1].get_value();
    }

    template<typename T>
    void Array<T>::set_element(int index, T val) {
        data[index].set_value(val);
    }

    template<typename T>
    void Array<T>::insert(int index, T value) {
        auto buff = new ArrayElement<int>[count + 1];
        for (int i = 0; i < count + 1; ++i){
            if (i < index){
                buff[i].set_value(data[i].get_value());
            }
            else if (i == index){
                buff[i].set_value(value);
            }
            else {
                buff[i].set_value(data[i - 1].get_value());
            }
        }
        data = buff;
        ++count;
    }

    template<typename T>
    Array<T> Array<T>::operator+(const Array<T> &Arr) {
        Array<T> buff (*this);
        for (int i = 0; i < Arr.count; ++i){
            buff.append(Arr.data[i].get_value());
        }
        return buff;
    }

    template<typename T>
    bool Array<T>::operator==(const Array<T> &Arr) {
        if (this->count != Arr.count){
            return false;
        }
        for (int i = 0; i < this->count; ++i){
            if (this->data[i].get_value() != Arr.data[i].get_value()){
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
                    buff.append(this->data[i].get_value());
                }
            }
            return buff;
        }
    }

    template<typename T>
    int Array<T>::get_index(T val) {
        for (int i = 0; i < count; ++i){
            if (data[i].get_value() == val){
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    T Array<T>::operator[](int index) {
        return data[index].get_value();
    }

    template<typename T>
    typename Array<T>::ArrIterator Array<T>::begin() {
        return data;
    }

    template<typename T>
    typename Array<T>::ArrIterator Array<T>::end() {
        return data + count;
    }


//    template<typename T>
//    void Array<T>::sorted(const std::string& order) {
//        if (order == "ASC") {
//        }
//        else if (order == "DESC"){
//
//        }
//    }



#endif
