#ifndef SET_COLLECTION_LIST_ELEMENT_H
#define SET_COLLECTION_LIST_ELEMENT_H
    template <typename T>
    class ListElement{
        private:
            ListElement<T> *next;
            ListElement<T> *prev;
            T data;
        public:
            explicit ListElement(T);
            ~ListElement();
            ListElement<T> *get_next();
            ListElement<T> *get_prev();
            void set_prev(ListElement<T> *);
            void set_next(ListElement<T> *);
            T get_data();
            void set_data(T);
    };

    template<typename T>
    ListElement<T>::ListElement(T val) {
        this->next = nullptr;
        this->prev = nullptr;
        this->data = val;
    }

    template<typename T>
    ListElement<T> *ListElement<T>::get_next() {
        return this->next;
    }

    template<typename T>
    ListElement<T> *ListElement<T>::get_prev() {
        return this->prev;
    }

    template<typename T>
    T ListElement<T>::get_data() {
        return this->data;
    }

    template<typename T>
    void ListElement<T>::set_data(T val) {
        this->data = val;
    }

    template<typename T>
    void ListElement<T>::set_prev(ListElement<T> *p_prev) {
        this->prev = p_prev;
    }

    template<typename T>
    void ListElement<T>::set_next(ListElement<T> *p_next) {
        this->next = p_next;
    }

template<typename T>
    ListElement<T>::~ListElement() = default;

#endif
