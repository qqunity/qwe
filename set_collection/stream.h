#ifndef SET_COLLECTION_STREAM_H
#define SET_COLLECTION_STREAM_H
    #include "mutable_sequence.h"
    #include <string>
    #include <ctime>

    template<typename T, class C>
    class Stream{
        private:
            MutableSequence<T, C> stream_data;
            int stream_size;
            bool ability_to_write;
            bool ability_to_read;
            bool ability_to_seek;
            bool ability_to_timeout;
            int creation_time;
            int timeout;
        public:
            Stream(bool = true, bool = true, bool = true, bool = false, int = -1);
            Stream(Stream<T, C> &);
            Stream(T *, int);
            Stream(MutableSequence<T, C> &);
            bool can_read();
            bool can_seek();
            bool can_write();
            bool can_timeout();
            void set_ability_to_write(bool);
            void set_ability_to_read(bool);
            void set_ability_to_seek(bool);
            void set_ability_to_timeout(bool);
            void set_timeout(int);
            void check_timeout(bool = false);
            void push(T);
            void pop();
            void dispose();
            auto *front();
            auto *back();
            bool empty();
            void swap(int, int);
            Stream<T, C> reversed();
            int length(std::string = "elements");
            Stream<T, C> operator << (T);
            T operator >> (T &);
            Stream<T, C> &operator = (const Stream<T, C> &);
            Stream<T, C> operator + (Stream<T, C> &);
            MutableSequence<T, C> operator * ();
            auto begin();
            auto end();
            ~Stream();
            template<typename T1, class C1> friend std::ostream& operator<< (std::ostream &, Stream<T1, C1> &);
    };

    template<typename T, class C>
    Stream<T, C>::Stream(bool ability_to_write, bool ability_to_read, bool ability_to_seek, bool ability_to_timeout, int timeout) {
        this->ability_to_write = ability_to_write;
        this->ability_to_read = ability_to_read;
        this->ability_to_seek = ability_to_seek;
        this->ability_to_timeout = ability_to_timeout;
        this->timeout = timeout;
        this->creation_time = ability_to_timeout ? time(NULL) : -1;
        this->stream_size = this->stream_data.length();
    }

    template<typename T, class C>
    bool Stream<T, C>::can_write() {
        this->check_timeout();
        return this->ability_to_write;
    }

    template<typename T, class C>
    bool Stream<T, C>::can_read() {
        this->check_timeout();
        return this->ability_to_read;
    }

    template<typename T, class C>
    bool Stream<T, C>::can_seek() {
        this->check_timeout();
        return this->ability_to_seek;
    }

    template<typename T, class C>
    void Stream<T, C>::check_timeout(bool show_the_remaining_time) {
        if (this->ability_to_timeout && (time(NULL) - this->creation_time >= this->timeout)){
            std::cout << "Stream::TimeoutError";
            this->dispose();
        }
        else {
            if (show_the_remaining_time){
                std::cout << this->timeout - (time(NULL) - this->creation_time) << " seconds left...";
            }
        }
    }

template<typename T, class C>
bool Stream<T, C>::can_timeout() {
    this->check_timeout();
    return this->ability_to_timeout;
}

    template<typename T, class C>
    int Stream<T, C>::length(std::string params) {
        this->check_timeout();
        if (params == "bytes"){
            if (this->stream_size == 0){
                return 0;
            }
            else {
                return this->stream_size * sizeof(*this->stream_data.get_element_ptr(0));
            }
        }
        else if(params == "elements"){
            return this->stream_size;
        }
        return 0;
    }

    template<typename T, class C>
    Stream<T, C> Stream<T, C>::operator<<(T val) {
        if (this->ability_to_write) {
            this->check_timeout();
            Stream<T, C> buff(*this);
            buff.push(val);
            return buff;
        }
        else {
            std::cout << "Stream::WriteError" << std::endl;
        }
    }

    template<typename T, class C>
    Stream<T, C>::Stream(Stream<T, C> &S) {
        this->stream_size = S.stream_size;
        this->stream_data = S.stream_data;
        this->ability_to_timeout = S.ability_to_timeout;
        this->timeout = S.timeout;
        this->ability_to_seek = this->ability_to_seek;
        this->creation_time = S.creation_time;
        this->ability_to_write = S.ability_to_write;
        this->ability_to_read = S.ability_to_read;
    }

    template<typename T, class C>
    void Stream<T, C>::push(T val) {
        if (this->ability_to_write) {
            this->check_timeout();
            this->stream_data.prepend(val);
            this->stream_size = this->stream_data.length();
        }
        else {
            std::cout << "Stream::WriteError" << std::endl;
        }
    }

    template<typename T1, class C1>
    std::ostream &operator<<(std::ostream &out, Stream<T1, C1> &S) {
        S.check_timeout();
        if (!S.empty()) {
            for (int i = 0; i < S.stream_size; ++i) {
                if (i == S.stream_size - 1) {
                    out << S.stream_data[i];
                } else {
                    out << S.stream_data[i] << " -> ";
                }
            }
        }
        else {
            out << "null";
        }
        return out;
    }

    template<typename T, class C>
    void Stream<T, C>::pop() {
        if (this->ability_to_write) {
            this->check_timeout();
            this->stream_data.pop(this->stream_size - 1);
            this->stream_size = this->stream_data.length();
        }
        else {
            std::cout << "Stream::WriteError" << std::endl;
        }
    }

    template<typename T, class C>
    auto *Stream<T, C>::front() {
        if (this->ability_to_seek) {
            this->check_timeout();
            return this->stream_data.get_element_ptr(this->stream_size - 1);
        }
        else {
            std::cout << "Stream::SeekError" << std::endl;
        }
    }

    template<typename T, class C>
    auto *Stream<T, C>::back() {
        if (this->ability_to_seek) {
            this->check_timeout();
            return this->stream_data.get_element_ptr(0);
        }
        else {
            std::cout << "Stream::SeekError" << std::endl;
        }
    }

    template<typename T, class C>
    T Stream<T, C>::operator>>(T &buff) {
        if (this->ability_to_read) {
            this->check_timeout();
            buff = this->stream_data[this->stream_size - 1];
            this->pop();
            return buff;
        }
        else {
            std::cout << "Stream::ReadError" << std::endl;
        }
    }

    template<typename T, class C>
    void Stream<T, C>::set_ability_to_write(bool val) {
        this->check_timeout();
        this->set_ability_to_write = val;
    }

    template<typename T, class C>
    void Stream<T, C>::set_ability_to_read(bool val) {
        this->check_timeout();
        this->set_ability_to_read = val;
    }

    template<typename T, class C>
    void Stream<T, C>::set_ability_to_seek(bool val) {
        this->check_timeout();
        this->set_ability_to_seek = val;
    }

    template<typename T, class C>
    void Stream<T, C>::set_ability_to_timeout(bool val) {
        this->check_timeout();
        this->ability_to_timeout = val;
    }

    template<typename T, class C>
    void Stream<T, C>::set_timeout(int val) {
        this->check_timeout();
        this->timeout = val;
    }

    template<typename T, class C>
    bool Stream<T, C>::empty() {
        this->check_timeout();
        return this->stream_size == 0;
    }

    template<typename T, class C>
    Stream<T, C>::Stream(T *mas, int n) {
        this->ability_to_write = true;
        this->ability_to_read = true;
        this->ability_to_seek = true;
        this->ability_to_timeout = false;
        this->timeout = -1;
        this->creation_time = -1;
        C buff(mas, n);
        this->stream_data = buff;
        this->stream_size = this->stream_data.length();
    }

    template<typename T, class C>
    Stream<T, C>::Stream(MutableSequence<T, C> &MS) {
        this->ability_to_write = true;
        this->ability_to_read = true;
        this->ability_to_seek = true;
        this->ability_to_timeout = false;
        this->timeout = -1;
        this->creation_time = -1;
        MutableSequence<T, C> buff(MS);
        this->stream_data = buff;
        this->stream_size = this->stream_data.length();
    }

    template<typename T, class C>
    void Stream<T, C>::dispose() {
        this->stream_data.del();
        this->stream_size = this->stream_data.length();
    }

    template<typename T, class C>
    void Stream<T, C>::swap(int index1, int index2) {
        if (this->ability_to_write){
            this->check_timeout();
            this->stream_data.swap(index1, index2);
        }
        else {
            std::cout << "Stream::WriteError" << std::endl;
        }
    }

template<typename T, class C>
Stream<T, C> Stream<T, C>::reversed() {
    this->check_timeout();
    MutableSequence<T, C> buff_ms = this->stream_data.reversed();
    Stream<T, C> buff(buff_ms);
    return buff;
}

    template<typename T, class C>
    Stream<T, C> &Stream<T, C>::operator=(const Stream<T, C> &S) {
        this->check_timeout();
        if (this == &S){
            return *this;
        }
        this->dispose();
        this->stream_size = S.stream_size;
        this->stream_data = S.stream_data;
        this->ability_to_timeout = S.ability_to_timeout;
        this->timeout = S.timeout;
        this->ability_to_seek = this->ability_to_seek;
        this->creation_time = S.creation_time;
        this->ability_to_write = S.ability_to_write;
        this->ability_to_read = S.ability_to_read;
        return *this;
    }

    template<typename T, class C>
    Stream<T, C> Stream<T, C>::operator+(Stream<T, C> &S) {
        this->check_timeout();
        Stream<T, C> buff(*this);
        for (int i = S.stream_size - 1; i >= 0; ++i){
             buff.push(S.stream_data[i]);
        }
        return buff;
    }

    template<typename T, class C>
    MutableSequence<T, C> Stream<T, C>::operator*() {
        this->check_timeout();
        return this->stream_data;
    }

    template<typename T, class C>
    auto Stream<T, C>::begin() {
        this->check_timeout();
        return this->stream_data.begin();
    }

    template<typename T, class C>
    auto Stream<T, C>::end() {
        return this->stream_data.end();
    }


    template<typename T, class C>
    Stream<T, C>::~Stream() = default;


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

    
#endif
