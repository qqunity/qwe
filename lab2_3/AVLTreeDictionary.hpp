#ifndef LAB_2_AVLTREEDICTIONARY_HPP
#define LAB_2_AVLTREEDICTIONARY_HPP

#include "KVElement.hpp"
#include "AVLTree.hpp"
#include "IDictionary.hpp"
#include "Sequence.hpp"

namespace dictionary {
    template<typename K, typename V>
    class AVLTreeDictionary: public IDictionary<K, V> {
    private:
        tree::AVLTree<KVElement<K, V>> *tree;
    public:
        AVLTreeDictionary(const std::string &sequenceType, K defaultKey, V defaultValue);

        AVLTreeDictionary(const AVLTreeDictionary<K, V> &dict);

        void insert (K key, V value) override;

        KVElement<K, V> &get(K key) override;

        KVElement<K, V> &operator[](K key) override;

        sequence::SequenceIterator<V> values() override;

        sequence::SequenceIterator<Pair<K, V>> items() override;

        bool contains(K key) override;

        void remove(K key) override;

        template<typename K1, typename  V1>
        friend std::ostream &operator<<(std::ostream &out, AVLTreeDictionary<K1, V1> &dict);

        ~AVLTreeDictionary();
    };

    template<typename K, typename V>
    AVLTreeDictionary<K, V>::AVLTreeDictionary(const std::string &sequenceType, K defaultKey, V defaultValue): IDictionary<K, V>(0, sequenceType, defaultKey, defaultValue) {
        this->tree = new tree::AVLTree<KVElement<K, V>>(this->defaultElement);
    }

    template<typename K, typename V>
    AVLTreeDictionary<K, V>::AVLTreeDictionary(const AVLTreeDictionary<K, V> &dict) {
        this->t = dict.t;
        this->defaultElement = dict.defaultElement;
        this->sequenceType = dict.sequenceType;
        if (this->sequenceType == "ArraySequence") {
            this->keysSequence = new array::ArraySequence<K>();
        } else {
            this->keysSequence = new list::LinkedListSequence<K>();
        }
        this->size = 0;
        this->tree = new tree::AVLTree<KVElement<K, V>>(this->defaultElement);
        for (unsigned int i = 0; i < dict.size; ++i) {
            auto *element = new KVElement<K, V>((*dict.keysSequence)[i]->getValue(), this->defaultElement.getValue());
            this->tree->insert(dict.tree->search(*element));
            this->keysSequence->prepend((*dict.keysSequence)[i]->getValue());
            this->sortKeys();
            ++this->size;
        }
    }

    template<typename K, typename V>
    void AVLTreeDictionary<K, V>::insert(K key, V value) {
        auto *element = new KVElement<K, V>(key, value);
        if (this->tree->search(*element) == this->defaultElement) {
            this->keysSequence->prepend(key);
            this->tree->insert(*element);
            this->sortKeys();
            ++this->size;
        } else {
            throw exceptions::AVLTreeDictionaryException("Key already exists", __LINE__, __FILE__);
        }
    }

    template<typename K, typename V>
    KVElement<K, V> &AVLTreeDictionary<K, V>::get(K key) {
        auto *element = new KVElement<K, V>(key, this->defaultElement.getValue());
        if (this->tree->search(*element) != this->defaultElement) {
            return this->tree->search(*element);
        } else {
            throw exceptions::AVLTreeDictionaryException("Key has no exists", __LINE__, __FILE__);
        }
    }

    template<typename K, typename V>
    KVElement<K, V> &AVLTreeDictionary<K, V>::operator[](K key) {
        auto *element = new KVElement<K, V>(key, this->defaultElement.getValue());
        if (this->tree->search(*element) == this->defaultElement) {
            this->keysSequence->prepend(key);
            this->tree->insert(*element);
            this->sortKeys();
            ++this->size;
        }
        return this->tree->search(*element);
    }

    template<typename K, typename V>
    sequence::SequenceIterator<V> AVLTreeDictionary<K, V>::values() {
        sequence::Sequence<V> *seq;
        if (this->sequenceType == "ArraySequence") {
            seq = new array::ArraySequence<V>();
        } else {
            seq = new list::LinkedListSequence<V>();
        }
        for (unsigned int i = 0; i < this->size; ++i) {
            auto *element = new KVElement<K, V>((*this->keysSequence)[i]->getValue(), this->defaultElement.getValue());
            V value = this->tree->search(*element).getValue();
            seq->append(value);
        }
        auto iter = new sequence::SequenceIterator<V>(seq);
        return *iter;
    }

    template<typename K, typename V>
    sequence::SequenceIterator<Pair<K, V>> AVLTreeDictionary<K, V>::items() {
        sequence::Sequence<Pair<K, V>> *seq;
        if (this->sequenceType == "ArraySequence") {
            seq = new array::ArraySequence<Pair<K, V>>();
        } else {
            seq = new list::LinkedListSequence<Pair<K, V>>();
        }
        for (unsigned int i = 0; i < this->size; ++i) {
            auto  key = (*this->keysSequence)[i]->getValue();
            auto *element = new KVElement<K, V>(key, this->defaultElement.getValue());
            V value = this->tree->search(*element).getValue();
            seq->append(std::make_pair(key, value));
        }
        auto iter = new sequence::SequenceIterator<Pair<K, V>>(seq);
        return *iter;
    }

    template<typename K, typename V>
    bool AVLTreeDictionary<K, V>::contains(K key) {
        auto *element = new KVElement<K, V>(key, this->defaultElement.getValue());
        return this->tree->search(*element) != this->defaultElement;
    }

    template<typename K, typename V>
    void AVLTreeDictionary<K, V>::remove(K key) {
        auto *element = new KVElement<K, V>(key, this->defaultElement.getValue());
        if (this->tree->search(*element) != this->defaultElement) {
            this->tree->remove(*element);
            this->keysSequence->pop(this->keysSequence->getIndex(key));
            --this->size;
        } else {
            throw exceptions::AVLTreeDictionaryException("Key has no exists", __LINE__, __FILE__);
        }
    }

    template<typename K1, typename V1>
    std::ostream &operator<<(std::ostream &out, AVLTreeDictionary<K1, V1> &dict) {
        if (dict.size != 0) {
            out << "{";
            for (unsigned int i = 0; i < dict.size; ++i) {
                auto element = new KVElement<K1, V1>((*dict.keysSequence)[i]->getValue(), dict.defaultElement.getValue());
                auto el = dict.tree->search(*element);
                if (i == dict.size - 1) {
                    out << el << "}";
                } else {
                    out << el <<", ";
                }
            }
        } else {
            out << "null";
        }
        return out;
    }

    template<typename K, typename V>
    AVLTreeDictionary<K, V>::~AVLTreeDictionary() = default;
}

#endif
