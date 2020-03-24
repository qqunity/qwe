#ifndef SET_COLLECTION_LIST_SEQUENCE_H
#define SET_COLLECTION_LIST_SEQUENCE_H

    #include "list.h"

    template<typename  T>
    class ListSequence{
    private:
        List<T> sequence_data;
        int sequence_size;
    public:
        ListSequence();
        ListSequence(T *, int);
        ListSequence(const List<T> &);
        ListSequence(ListSequence<T> &);
        ~ListSequence();
        void append(T);
        void prepend(T);
        int length();
        void pop(int);
        void del();
        void swap(int, int);
        ListSequence<T> reversed();
        T get_element(int);
        int get_index(T);
        ListElement<T> *get_element_ptr(int);
        T get_first();
        T get_last();
        void insert(int, T);
        void set_element(int, T);
        ListSequence<T> &operator = (const ListSequence<T> &);
        ListSequence<T> operator + (ListSequence<T> &);
        bool operator == (ListSequence<T> &);
        bool operator != (ListSequence<T> &);
        T operator [] (int);
        ListSequence<T> operator * (int);
        class ListSequenceIterator {
        private:
            ListElement<T> *cur_o;
        public:
            ListSequenceIterator(ListElement<T> *);
            ListElement<T> &operator + (int );
            ListElement<T> &operator - (int );
            ListElement<T> operator ++ (int);
            ListElement<T> operator -- (int);
            ListElement<T> &operator ++ ();
            ListElement<T> &operator -- ();
            ListElement<T> &operator = (ListElement<T> &);
            bool operator != (const ListSequenceIterator &);
            bool operator == (const ListSequenceIterator &);
            ListElement<T> &operator * ();
        };
        ListSequenceIterator begin();
        ListSequenceIterator end();
        template<typename T1> friend std::ostream& operator<< (std::ostream &, const ListSequence<T1> &);
    };

    template<typename T>
    ListSequence<T>::ListSequenceIterator::ListSequenceIterator(ListElement<T> *first_o) {
        this->cur_o = first_o;
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator+(int n) {
        ListElement<T> *buff = this->cur_o;
        for (int i = 0; i < n && buff != nullptr; ++i){
            buff = buff->get_next();
        }
        return *buff;
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator-(int n) {
        ListElement<T> *buff = this->cur_o;
        for (int i = 0; i < n && buff != nullptr; ++i){
            buff = buff->get_prev();
        }
        return *buff;
    }

    template<typename T>
    ListElement<T> ListSequence<T>::ListSequenceIterator::operator++(int) {
        this->cur_o = this->cur_o->get_next();
        return *(this->cur_o->get_prev);
    }

    template<typename T>
    ListElement<T> ListSequence<T>::ListSequenceIterator::operator--(int) {
        this->cur_o = this->cur_o->get_prev();
        return *(this->cur_o->get_next());
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator++() {
        this->cur_o = this->cur_o->get_next();
        return *(this->cur_o);
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator--() {
        this->cur_o = this->cur_o->get_prev();
        return *(this->cur_o);
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator=(ListElement<T> &It) {
        return this->cur_o != It.cur_o;
    }

    template<typename T>
    bool ListSequence<T>::ListSequenceIterator::operator!=(const ListSequence::ListSequenceIterator &It) {
        return this->cur_o != It.cur_o;
    }

    template<typename T>
    bool ListSequence<T>::ListSequenceIterator::operator==(const ListSequence::ListSequenceIterator &It) {
        return this->cur_o == It.cur_o;
    }

    template<typename T>
    ListElement<T> &ListSequence<T>::ListSequenceIterator::operator*() {
        return *this->cur_o;
    }

template<typename T>
    ListSequence<T>::ListSequence() {
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    int ListSequence<T>::length() {
        return this->sequence_size;
    }

    template<typename T>
    ListSequence<T>::ListSequence(T *mas, int n) {
        for (int i = 0; i < n; ++i){
            this->sequence_data.append(mas[i]);
        }
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    ListSequence<T>::ListSequence(ListSequence<T> &ArrS) {
        this->sequence_size = ArrS.sequence_size;
        for (int i = 0; i < this->sequence_size; ++i){
            this->sequence_data.append(ArrS.sequence_data[i]);
        }
    }

    template<typename T>
    void ListSequence<T>::append(T val) {
        this->sequence_data.append(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ListSequence<T>::prepend(T val) {
        this->sequence_data.prepend(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ListSequence<T1> &ArrS) {
        out << ArrS.sequence_data;
        return out;
    }

    template<typename T>
    void ListSequence<T>::pop(int index) {
        this->sequence_data.pop(index);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ListSequence<T>::del() {
        this->sequence_data.del();
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ListSequence<T>::swap(int index1, int index2) {
        this->sequence_data.swap(index1, index2);
    }

    template<typename T>
    ListSequence<T>::ListSequence(const List<T> &L) {
        this->sequence_data = L;
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    ListSequence<T> ListSequence<T>::reversed() {
        ListSequence<T> buff;
        for (int i = this->sequence_size - 1; i >= 0; --i){
            buff.append(this->sequence_data[i]);
        }
        return buff;
    }

    template<typename T>
    T ListSequence<T>::get_element(int index) {
        return this->sequence_data[index];
    }

    template<typename T>
    int ListSequence<T>::get_index(T val) {
        return this->sequence_data.get_index(val);
    }

    template<typename T>
    T ListSequence<T>::get_first() {
        return this->sequence_data.get_first();
    }

    template<typename T>
    T ListSequence<T>::get_last() {
        return this->sequence_data.get_last();
    }

    template<typename T>
    void ListSequence<T>::insert(int index, T val) {
        this->sequence_data.insert(index, val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T>
    void ListSequence<T>::set_element(int index, T val) {
        this->sequence_data.set_element(index, val);
    }

    template<typename T>
    ListSequence<T> &ListSequence<T>::operator=(const ListSequence<T> &ArrS) {
        if (this == &ArrS){
            return *this;
        }
        this->~ListSequence();
        this->sequence_size = ArrS.sequence_size;
        this->sequence_data =ArrS.sequence_data;
        return *this;
    }

    template<typename T>
    ListSequence<T> ListSequence<T>::operator+(ListSequence<T> &ArrS) {
        ListSequence<T> buff(*this);
        for (int i = 0; i < ArrS.sequence_size; ++i){
            buff.append(ArrS.sequence_data[i]);
        }
        return buff;
    }

    template<typename T>
    bool ListSequence<T>::operator==(ListSequence<T> &ArrS) {
        return this->sequence_data == ArrS.sequence_data;
    }

    template<typename T>
    bool ListSequence<T>::operator!=(ListSequence<T> &ArrS) {
        return this->sequence_data != ArrS.sequence_data;
    }

    template<typename T>
    T ListSequence<T>::operator[](int index) {
        return this->sequence_data[index];
    }

    template<typename T>
    ListSequence<T> ListSequence<T>::operator*(int k) {
        if (k == 0){
            ListSequence<T> buff;
            return buff;
        }
        else {
            ListSequence<T> buff(*this);
            for (int i = 1; i < k; ++i){
                for (int j = 0; j < this->sequence_size; ++j){
                    buff.append(this->sequence_data[j]);
                }
            }
            return buff;
        }
    }

    template<typename T>
    typename ListSequence<T>::ListSequenceIterator ListSequence<T>::begin() {
        return this->sequence_data.get_head_ptr();
    }

    template<typename T>
    typename ListSequence<T>::ListSequenceIterator ListSequence<T>::end() {
        return this->sequence_data.get_tail_ptr()->get_next();
    }

    template<typename T>
    ListElement<T> *ListSequence<T>::get_element_ptr(int index) {
        return this->sequence_data.get_element_ptr(index);
    }

template<typename T>
    ListSequence<T>::~ListSequence() = default;
#endif
