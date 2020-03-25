#ifndef SET_COLLECTION_MUTABLE_SEQUENCE_H
#define SET_COLLECTION_MUTABLE_SEQUENCE_H

    #include "array_sequence.h"
    #include "list_sequence.h"
    #include <cstdarg>
    #include <algorithm>

    template<typename T, class C>
    class MutableSequence{
        private:
            C sequence_data;
            int sequence_size;
        public:
            MutableSequence();
            MutableSequence(T *, int);
            ~MutableSequence();
            MutableSequence(const C &);
            MutableSequence(MutableSequence<T, C> &);
            void append(T);
            void prepend(T);
            int length();
            void pop(int);
            void del();
            void swap(int, int);
            MutableSequence<T, C> reversed();
            T get_element(int);
            int get_index(T);
            auto *get_element_ptr(int);
            T get_first();
            T get_last();
            void insert(int, T);
            void set_element(int, T);
            MutableSequence<T, C> &operator = (const MutableSequence<T, C> &);
            MutableSequence<T, C> operator + (MutableSequence<T, C> &);
            bool operator == (MutableSequence<T, C> &);
            bool operator != (MutableSequence<T, C> &);
            MutableSequence<T, C> operator * (int);
            T operator [] (int);
            auto begin();
            auto end();
            template<typename T1, class C1> friend std::ostream& operator<< (std::ostream &, const MutableSequence<T1, C1> &);

    };

    template<typename T, class C>
    MutableSequence<T, C>::MutableSequence() {
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    MutableSequence<T, C>::MutableSequence(T *mas, int n) {
        for (int i = 0; i < n; ++i){
            this->sequence_data.append(mas[i]);
        }
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T1, class C1>
    std::ostream &operator<<(std::ostream &out, const MutableSequence<T1, C1> &MS) {
        out << MS.sequence_data;
        return out;
    }

    template<typename T, class C>
    MutableSequence<T, C>::MutableSequence(const C &C_S) {
        this->sequence_data =C_S;
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    MutableSequence<T, C>::MutableSequence(MutableSequence<T, C> &MS) {
        this->sequence_size = MS.sequence_size;
        for (int i = 0; i < this->sequence_size; ++i){
            this->sequence_data.append(MS.sequence_data[i]);
        }
    }

    template<typename T, class C>
    void MutableSequence<T, C>::append(T val) {
        this->sequence_data.append(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    void MutableSequence<T, C>::prepend(T val) {
        this->sequence_data.prepend(val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    int MutableSequence<T, C>::length() {
        return this->sequence_size;
    }

    template<typename T, class C>
    void MutableSequence<T, C>::pop(int index) {
        this->sequence_data.pop(index);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    void MutableSequence<T, C>::del() {
        this->sequence_data.del();
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    void MutableSequence<T, C>::swap(int index1, int index2) {
        this->sequence_data.swap(index1, index2);
    }

    template<typename T, class C>
    MutableSequence<T, C> MutableSequence<T, C>::reversed() {
        MutableSequence<T, C> buff;
        for (int i = this->sequence_size - 1; i >= 0; --i){
            buff.append(this->sequence_data[i]);
        }
        return buff;
    }

    template<typename T, class C>
    T MutableSequence<T, C>::get_element(int index) {
        return this->sequence_data[index];
    }

    template<typename T, class C>
    int MutableSequence<T, C>::get_index(T val) {
        return this->sequence_data.get_index(val);
    }

    template<typename T, class C>
    T MutableSequence<T, C>::get_first() {
        return this->sequence_data.get_first();
    }

    template<typename T, class C>
    T MutableSequence<T, C>::get_last() {
        return this->sequence_data.get_last();
    }

    template<typename T, class C>
    void MutableSequence<T, C>::insert(int index, T val) {
        this->sequence_data.insert(index, val);
        this->sequence_size = this->sequence_data.length();
    }

    template<typename T, class C>
    void MutableSequence<T, C>::set_element(int index, T val) {
        this->sequence_data.set_element(index, val);
    }

    template<typename T, class C>
    MutableSequence<T, C> &MutableSequence<T, C>::operator=(const MutableSequence<T, C> &MS) {
        if (this == &MS){
            return *this;
        }
        this->~MutableSequence();
        this->sequence_size = MS.sequence_size;
        this->sequence_data = MS.sequence_data;
        return *this;
    }

    template<typename T, class C>
    MutableSequence<T, C> MutableSequence<T, C>::operator+(MutableSequence<T, C> &MS) {
        MutableSequence<T, C> buff(*this);
        for (int i = 0; i < MS.sequence_size; ++i){
            buff.append(MS.sequence_data[i]);
        }
        return buff;
    }

    template<typename T, class C>
    bool MutableSequence<T, C>::operator==(MutableSequence<T, C> &MS) {
        return this->sequence_data == MS.sequence_data;
    }

    template<typename T, class C>
    bool MutableSequence<T, C>::operator!=(MutableSequence<T, C> &MS) {
        return this->sequence_data != MS.sequence_data;
    }

template<typename T, class C>
MutableSequence<T, C> MutableSequence<T, C>::operator*(int k) {
    if (k == 0){
        MutableSequence<T, C> buff;
        return buff;
    }
    else {
        MutableSequence<T,  C> buff(*this);
        for (int i = 1; i < k; ++i){
            for (int j = 0; j < this->sequence_size; ++j){
                buff.append(this->sequence_data[j]);
            }
        }
        return buff;
    }
}

    template<typename T, class C>
    T MutableSequence<T, C>::operator[](int index) {
        return this->sequence_data[index];
    }

    template<typename T, class C>
    auto MutableSequence<T, C>::begin() {
        return this->sequence_data.begin();
    }

    template<typename T, class C>
    auto MutableSequence<T, C>::end() {
        return this->sequence_data.end();
    }

    template<typename T, class C>
    auto *MutableSequence<T, C>::get_element_ptr(int index) {
        return this->sequence_data.get_element_ptr(index);
    }


template<typename T, class C>
    MutableSequence<T, C>::~MutableSequence() = default;

    template<typename InputIterator, typename Function>
    void map(InputIterator first_it, InputIterator last_it, Function f){
        while (first_it != last_it){
            f(*first_it);
            ++first_it;
        }
    }

    template<typename T, typename InputIterator, typename Function>
    T where(InputIterator first_it, InputIterator last_it, Function f){
        T buff;
        while (first_it != last_it){
            if (f(*first_it)){
                buff.append((*first_it).get_data());
            }
            ++first_it;
        }
        return buff;
    }

    template<typename T, typename InputIterator, typename Function>
    T reduce(InputIterator first_it, InputIterator last_it, T c, Function f){
        T buff = f((*first_it).get_data(), c);
        ++first_it;
        while (first_it != last_it){
            buff = f((*first_it).get_data(), buff);
            ++first_it;
        }
        return buff;
    }

    template<typename T1, typename T2, typename list_T>
    list_T combine_these_structures(ListSequence<int> &meta_data, ...){
        list_T data;
        va_list argList;
        va_start(argList, meta_data);
        int number1 = meta_data[0];
        int number2 = meta_data[1];
        for(int i = 0; i < number1; ++i) {
            data.append(&va_arg(argList, T1));
            meta_data.append(0);
        }
        for(int i = 0; i < number2; ++i) {
            data.append(&va_arg(argList, T2));
            meta_data.append(1);
        }
        meta_data.pop(0);
        meta_data.pop(0);
        va_end(argList);
        return data;
    }

    template<typename list_T, typename T>
    int min_sequence_len(ListSequence<int> meta_data, list_T data){
        int mn_len = INT32_MAX;
        for (int i = 0; i < data.length(); ++i){
            if (meta_data[i] == 0){
                auto data_el = *dynamic_cast<ListSequence<T> *>(data[i]);
                mn_len = std::min(mn_len, data_el.length());
            }
            else if (meta_data[i] == 1) {
                auto data_el = *dynamic_cast<ArraySequence<T> *>(data[i]);
                mn_len = std::min(mn_len, data_el.length());
            }
        }
        return mn_len;
    }

    template<typename seq_T, typename list_T, typename T>
    seq_T zip(ListSequence<int> meta_data, list_T data){
        seq_T zip_seq;
        int cnt_el = min_sequence_len<list_T, T>(meta_data, data);
        for (int i = 0; i < cnt_el; ++i){
            ListSequence<T> buff;
            for (int j = 0; j < data.length(); ++j){
                if (meta_data[j] == 0){
                    auto data_el = *dynamic_cast<ListSequence<T> *>(data[j]);
                    buff.append(data_el[i]);
                }
                else if (meta_data[j] == 1) {
                    auto data_el = *dynamic_cast<ArraySequence<T> *>(data[j]);
                    buff.append(data_el[i]);
                }
            }
            zip_seq.append(buff);
        }
        return zip_seq;
    }

    template<typename T>
    ListSequence<ListSequence<T>> unzip(ListSequence<ListSequence<T>> data){
        int cnt_list = data[0].length();
        ListSequence<ListSequence<T>> unzip_seq;
        for (int i = 0; i < cnt_list; ++i){
            ListSequence<T> buff;
            for (int j = 0; j < data.length(); ++j){
                buff.append(data[j][i]);
            }
            unzip_seq.append(buff);
        }
        std::cout << unzip_seq;
        return unzip_seq;
    }

#endif
