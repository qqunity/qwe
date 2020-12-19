#ifndef LAB_2_IDICTIONARY_HPP
#define LAB_2_IDICTIONARY_HPP

#include "Sequence.hpp"
#include "KVElement.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "SequenceIterator.hpp"
#include "Pair.hpp"
#include <string>

namespace dictionary {
    template <typename K, typename V>
    class IDictionary {
    protected:
        sequence::Sequence<K> *keysSequence;
        unsigned int size;
        unsigned int t{};
        std::string sequenceType;
        KVElement<K, V> defaultElement;
    protected:
        void sortKeys();
    public:
        IDictionary();

        IDictionary(unsigned int t, const std::string &sequenceType, K defaultKey, V defaultValue);

        virtual void insert (K key, V value) = 0;

        virtual KVElement<K, V> &get(K key) = 0;

        virtual KVElement<K, V> &operator[](K key) = 0;

        virtual bool contains(K key) = 0;

        sequence::SequenceIterator<K> keys();

        virtual sequence::SequenceIterator<V> values() = 0;

        virtual sequence::SequenceIterator<Pair<K, V>> items() = 0;

        unsigned int length();

        virtual void remove(K key) = 0;

        ~IDictionary();
    };

    template<typename K, typename V>
    IDictionary<K, V>::IDictionary(unsigned int t, const std::string &sequenceType, K defaultKey, V defaultValue) {
        this->t = t;
        if (sequenceType != "ArraySequence" && sequenceType != "LinkedListSequence") {
            throw exceptions::IDictionaryException("Invalid sequence type", __LINE__, __FILE__);
        } else {
            this->sequenceType = sequenceType;
            if (this->sequenceType == "ArraySequence") {
                this->keysSequence = new array::ArraySequence<K>();
            } else {
                this->keysSequence = new list::LinkedListSequence<K>();
            }
        }
        this->size = 0;
        this->defaultElement.setKV(defaultKey, defaultValue);
    }

    template<typename K, typename V>
    void IDictionary<K, V>::sortKeys() {
        unsigned int j = 0;
        while (j < this->size && (*this->keysSequence)[j]->getValue() <= (*this->keysSequence)[j + 1]->getValue()) {
            ++j;
        }
        while (j < this->size && (*this->keysSequence)[j]->getValue() > (*this->keysSequence)[j + 1]->getValue()) {
            this->keysSequence->swap(j, j + 1);
            ++j;
        }
    }

    template<typename K, typename V>
    sequence::SequenceIterator<K> IDictionary<K, V>::keys() {
        auto iter = new sequence::SequenceIterator<K>(this->keysSequence);
        return *iter;
    }

    template<typename K, typename V>
    unsigned int IDictionary<K, V>::length() {
        return this->size;
    }

    template<typename K, typename V>
    IDictionary<K, V>::IDictionary() = default;


    template<typename K, typename V>
    IDictionary<K, V>::~IDictionary() = default;
}

#endif
