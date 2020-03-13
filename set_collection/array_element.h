#ifndef SET_COLLECTION_ARRAY_ELEMENT_H
#define SET_COLLECTION_ARRAY_ELEMENT_H

    #include <iostream>

    template <typename T>
    class ArrayElement{
    private:
        T val;
        bool has_val;
    public:
        ArrayElement();
        bool has_value();
        void set_value(T);
        T get_value();
        ~ArrayElement();
    };

    template<typename T>
    bool ArrayElement<T>::has_value() {
        return has_val;
    }

    template<typename T>
    void ArrayElement<T>::set_value(T value) {
        val = value;
        has_val = true;
    }

    template<typename T>
    T ArrayElement<T>::get_value() {
        if (has_val){
            return val;
        }
        else {
            std::cout << "Element hasn't value!" << std::endl;
        }
    }

    template<typename T>
    ArrayElement<T>::ArrayElement() {
        has_val = false;
    }

    template<typename T>
    ArrayElement<T>::~ArrayElement() = default;


#endif
