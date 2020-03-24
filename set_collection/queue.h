#ifndef SET_COLLECTION_QUEUE_H
#define SET_COLLECTION_QUEUE_H

    #include "list.h"

    template<typename T>
    class Queue {
        private:
            List<T> q_data;
            int q_size;
        public:
            Queue();
            ~Queue();
            ListElement<T> *front();
            ListElement<T> *back();
            bool empty();
            int size();
            void push(T);
            void pop();
            void print_queue();
    };

    template<typename T>
    Queue<T>::Queue() {
        this->q_size = this->q_data.length();
    }

    template<typename T>
    Queue<T>::~Queue() {
        this->q_data.del();
        this->q_size = this->q_data.length();
    }

    template<typename T>
    ListElement<T> *Queue<T>::front() {
        return this->q_data.get_head_ptr();
    }

    template<typename T>
    ListElement<T> *Queue<T>::back() {
        return this->q_data.get_tail_ptr();
    }

    template<typename T>
    bool Queue<T>::empty() {
        return this->q_size == 0;
    }

    template<typename T>
    int Queue<T>::size() {
        return this->q_size;
    }

    template<typename T>
    void Queue<T>::push(T val) {
        this->q_data.append(val);
        this->q_size = this->q_data.length();
    }

    template<typename T>
    void Queue<T>::pop() {
        this->q_data.pop(0);
        this->q_size = this->q_data.length();
    }

    template<typename T>
    void Queue<T>::print_queue() {
        for (int i = 0; i < this->q_size; ++i){
            if (i == this->q_size - 1){
                std::cout << q_data[i] << std::endl;
            }
            else {
                std::cout << q_data[i] << " <- ";
            }
        }
    }


#endif
