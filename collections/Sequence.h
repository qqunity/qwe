#ifndef COLLECTIONS_SEQUENCE_H
#define COLLECTIONS_SEQUENCE_H

    namespace sequence {
        template<typename T>
        class Sequence {
        public:

            Sequence() = default;

            ~Sequence() = default;

            virtual int length() = 0;

            virtual void append(T) = 0;

            virtual void prepend(T) = 0;

            virtual void pop(int) = 0;

            virtual void remove() = 0;

            virtual void swap(int, int) = 0;

            virtual T getElement(int) = 0;

            virtual int getIndex(T) = 0;

            virtual void *getFirst() = 0;

            virtual void *getLast() = 0;

            virtual void insert(int, T) = 0;

            virtual void setElement(int, T) = 0;
        };

    }
#endif
