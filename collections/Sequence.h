#ifndef COLLECTIONS_SEQUENCE_H
#define COLLECTIONS_SEQUENCE_H

    template<typename T>
    class Sequence {

        protected:
            Sequence() = default;
        public:

            ~Sequence() = default;
            virtual void append(T) = 0;
            virtual void prepend(T) = 0;
            virtual int length() = 0;
            virtual void pop(int) = 0;
            virtual void del() = 0;
            virtual void swap(int, int) = 0;
            virtual T get_element(int) = 0;
            virtual int get_index(T) = 0;
            virtual T get_first() = 0;
            virtual T get_last() = 0;
            virtual void insert(int, T) = 0;
            virtual void set_element(int, T) = 0;
            virtual T operator [] (int) = 0;
    };
#endif
