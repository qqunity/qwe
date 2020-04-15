#ifndef COLLECTIONS_PAIR_H
#define COLLECTIONS_PAIR_H

    #include <iostream>

    template<typename T1, typename T2>
    class Pair {
        private:
            T1 element1;
            T2 element2;
        public:
            Pair();
            Pair(T1, T2);
            Pair(const Pair<T1, T2> &);
            void setFirst(T1);
            void setSecond(T2);
            T1 getFirst();
            T2 getSecond();
            Pair<T1, T2> &operator = (const Pair<T1, T2> &);
            bool operator == (Pair<T1, T2>);
            template<typename T11, typename T22>friend std::ostream &operator<<(std::ostream &, Pair<T11, T22>);
    };

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(T1 elem1, T2 elem2) {
        this->element1 = elem1;
        this->element2 = elem2;
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair(const Pair<T1, T2> &P) {
        this->element2 = P.element2;
        this->element1 = P.element1;
    }

    template<typename T1, typename T2>
    void Pair<T1, T2>::setFirst(T1 value) {
        this->element1 = value;
    }

    template<typename T1, typename T2>
    void Pair<T1, T2>::setSecond(T2 value) {
        this->element2 = value;
    }

    template<typename T1, typename T2>
    T1 Pair<T1, T2>::getFirst() {
        return this->element1;
    }

    template<typename T1, typename T2>
    T2 Pair<T1, T2>::getSecond() {
        return this->element2;
    }

    template<typename T1, typename T2>
    Pair<T1, T2> &Pair<T1, T2>::operator=(const Pair<T1, T2> &P) {
        if (this == &P){
            return *this;
        }
        this->element1 = P.element1;
        this->element2 = P.element2;
        return *this;
    }

    template<typename T11, typename T22>
    std::ostream &operator<<(std::ostream &out, Pair<T11, T22> P) {
        out << "<" << P.getFirst() << ", " << P.getSecond() << ">";
        return out;
    }

    template<typename T1, typename T2>
    bool Pair<T1, T2>::operator==(Pair<T1, T2> P) {
        return this->element1 == P.getFirst() && this->element2 == P.getSecond();
    }

    template<typename T1, typename T2>
    Pair<T1, T2>::Pair() = default;

#endif
