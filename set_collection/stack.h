#ifndef SET_COLLECTION_STACK_H
#define SET_COLLECTION_STACK_H

    #include "array.h"

    template<typename  T>
    class Stack{
    private:
        Array<T> s_data;
        int s_size;
    public:
        Stack();
        ~Stack();
        int size();
        bool empty();
        ArrayElement<T> *top();
        void push(T);
        void pop();
        void print_stack();
    };

    template<typename T>
    Stack<T>::Stack() {
        this->s_size = (this->s_data).length();
    }

    template<typename T>
    int Stack<T>::size() {
        return this->s_size;
    }

    template<typename T>
    Stack<T>::~Stack() {
        this->s_data.del();
        this->s_size = (this->s_data).length();
    }

    template<typename T>
    ArrayElement<T> *Stack<T>::top() {
        return this->s_data.get_element_ptr(0);
    }

    template<typename T>
    void Stack<T>::push(T val) {
        this->s_data.prepend(val);
        this->s_size = (this->s_data).length();
    }

    template<typename T>
    bool Stack<T>::empty() {
        return this->s_size == 0;
    }

    template<typename T>
    void Stack<T>::pop() {
        this->s_data.pop(0);
        this->s_size = (this->s_data).length();
    }

    template<typename T>
    void Stack<T>::print_stack() {
        for (int i = 0; i < this->s_size; ++i){
            if (i == this->s_size - 1){
                std::cout << this->s_data[i] << std::endl;
            }
            else {
                std::cout << this->s_data[i] << " -> ";
            }
        }
    }


#endif
