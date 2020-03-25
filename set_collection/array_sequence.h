#ifndef SET_COLLECTION_ARRAY_SEQUENCE_H
#define SET_COLLECTION_ARRAY_SEQUENCE_H

    #include "array.h"
    #include "sequence.h"

    template<typename  T>
    class ArraySequence : public Sequence<T>{
        private:
            Array<T> sequence_data;
            int sequence_size;
        public:
            ArraySequence();
            ArraySequence(T *, int);
            ArraySequence(const Array<T> &);
            ArraySequence(ArraySequence<T> &);
            ~ArraySequence();
            void append(T) override;
            void prepend(T) override;
            int length() override;
            void pop(int) override;
            void del() override;
            void swap(int, int) override;
            ArraySequence<T> reversed();
            T get_element(int) override;
            int get_index(T) override;
            ArrayElement<T> *get_element_ptr(int);
            T get_first() override;
            T get_last() override;
            void insert(int, T) override;
            void set_element(int, T) override;
            ArraySequence<T> &operator = (const ArraySequence<T> &);
            ArraySequence<T> operator + (ArraySequence<T> &);
            bool operator == (ArraySequence<T> &);
            bool operator != (ArraySequence<T> &);
            T operator [] (int) override;
            ArraySequence<T> operator * (int);
        class ArrSequenceIterator {
        private:
            ArrayElement<T> *cur_o;
        public:
            ArrSequenceIterator(ArrayElement<T> *);
            ArrayElement<T> &operator + (int );
            ArrayElement<T> &operator - (int );
            ArrayElement<T> &operator ++ (int);
            ArrayElement<T> &operator -- (int);
            ArrayElement<T> &operator ++ ();
            ArrayElement<T> &operator -- ();
            ArrayElement<T> &operator = (ArrayElement<T> &);
            bool operator != (const ArrSequenceIterator &);
            bool operator == (const ArrSequenceIterator &);
            ArrayElement<T> &operator * ();
        };
        ArrSequenceIterator begin();
        ArrSequenceIterator end();
            template<typename T1> friend std::ostream& operator<< (std::ostream &, const ArraySequence<T1> &);
    };

    template<typename T>
    ArraySequence<T>::ArrSequenceIterator::ArrSequenceIterator(ArrayElement<T> *first_o) {
        this->cur_o = first_o;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator+(int n) {
        return *(this->cur_o + n);
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator-(int n) {
        return *(this->cur_o - n);
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator++(int) {
        return *this->cur_o++;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator--(int) {
        return *this->cur_o--;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator++() {
        return *++this->cur_o;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator--() {
        return *--this->cur_o;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator=(ArrayElement<T> &It) {
        this->cur_o = &It;
        return *this->cur_o;
    }

    template<typename T>
    bool ArraySequence<T>::ArrSequenceIterator::operator!=(const ArraySequence::ArrSequenceIterator &It) {
        return this->cur_o != It.cur_o;
    }

    template<typename T>
    bool ArraySequence<T>::ArrSequenceIterator::operator==(const ArraySequence::ArrSequenceIterator &It) {
        return this->cur_o == It.cur_o;
    }

    template<typename T>
    ArrayElement<T> &ArraySequence<T>::ArrSequenceIterator::operator*() {
        return *this->cur_o;
    }


    template<typename T>
    ArraySequence<T>::ArraySequence() {
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    int ArraySequence<T>::length() {
        return this->sequence_size;
    }

    template<typename T>
    ArraySequence<T>::ArraySequence(T *mas, int n) {
        for (int i = 0; i < n; ++i){
            this->sequence_data.append(mas[i]);
        }
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    ArraySequence<T>::ArraySequence(ArraySequence<T> &ArrS) {
        this->sequence_size = ArrS.sequence_size;
        for (int i = 0; i < this->sequence_size; ++i){
            this->sequence_data.append(ArrS.sequence_data[i]);
        }
    }

    template<typename T>
    void ArraySequence<T>::append(T val) {
        this->sequence_data.append(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ArraySequence<T>::prepend(T val) {
        this->sequence_data.prepend(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ArraySequence<T1> &ArrS) {
        out << ArrS.sequence_data;
        return out;
    }

    template<typename T>
    void ArraySequence<T>::pop(int index) {
        this->sequence_data.pop(index);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ArraySequence<T>::del() {
        this->sequence_data.del();
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ArraySequence<T>::swap(int index1, int index2) {
        this->sequence_data.swap(index1, index2);
    }

    template<typename T>
    ArraySequence<T>::ArraySequence(const Array<T> &Arr) {
        this->sequence_data = Arr;
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    ArraySequence<T> ArraySequence<T>::reversed() {
        ArraySequence<T> buff;
        for (int i = this->sequence_size - 1; i >= 0; --i){
            buff.append(this->sequence_data[i]);
        }
        return buff;
    }

    template<typename T>
    T ArraySequence<T>::get_element(int index) {
        return this->sequence_data[index];
    }

    template<typename T>
    int ArraySequence<T>::get_index(T val) {
        return this->sequence_data.get_index(val);
    }

    template<typename T>
    T ArraySequence<T>::get_first() {
        return this->sequence_data.get_first();
    }

    template<typename T>
    T ArraySequence<T>::get_last() {
        return this->sequence_data.get_last();
    }

    template<typename T>
    void ArraySequence<T>::insert(int index, T val) {
        this->sequence_data.insert(index, val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ArraySequence<T>::set_element(int index, T val) {
        this->sequence_data.set_element(index, val);
    }

    template<typename T>
    ArraySequence<T> &ArraySequence<T>::operator=(const ArraySequence<T> &ArrS) {
        if (this == &ArrS){
            return *this;
        }
        this->~ArraySequence();
        this->sequence_size = ArrS.sequence_size;
        this->sequence_data =ArrS.sequence_data;
        return *this;
    }

    template<typename T>
    ArraySequence<T> ArraySequence<T>::operator+(ArraySequence<T> &ArrS) {
        ArraySequence<T> buff(*this);
        for (int i = 0; i < ArrS.sequence_size; ++i){
            buff.append(ArrS.sequence_data[i]);
        }
        return buff;
    }

    template<typename T>
    bool ArraySequence<T>::operator==(ArraySequence<T> &ArrS) {
        return this->sequence_data == ArrS.sequence_data;
    }

    template<typename T>
    bool ArraySequence<T>::operator!=(ArraySequence<T> &ArrS) {
        return this->sequence_data != ArrS.sequence_data;
    }

    template<typename T>
    T ArraySequence<T>::operator[](int index) {
        return this->sequence_data[index];
    }

    template<typename T>
    ArraySequence<T> ArraySequence<T>::operator*(int k) {
        if (k == 0){
            ArraySequence<T> buff(0);
            return buff;
        }
        else {
            ArraySequence<T> buff(*this);
            for (int i = 1; i < k; ++i){
                for (int j = 0; j < this->sequence_size; ++j){
                    buff.append(this->sequence_data[j]);
                }
            }
            return buff;
        }
    }

    template<typename T>
    typename ArraySequence<T>::ArrSequenceIterator ArraySequence<T>::begin() {
        return this->sequence_data.get_element_ptr(0);
    }

    template<typename T>
    typename ArraySequence<T>::ArrSequenceIterator ArraySequence<T>::end() {
        return this->sequence_data.get_element_ptr(0) + this->sequence_size;
    }

    template<typename T>
    ArrayElement<T> *ArraySequence<T>::get_element_ptr(int index) {
        return this->sequence_data.get_element_ptr(index);
    }

template<typename T>
    ArraySequence<T>::~ArraySequence() = default;

#endif
