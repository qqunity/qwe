#ifndef COLLECTIONS_STREAM_H
#define COLLECTIONS_STREAM_H
    #include "ArraySequence.h"
    #include "ListSequence.h"
    #include "string"
    #include "Exceptions.h"

    namespace stream {
        template<typename T>
        class Stream {
            private:
                sequence::Sequence<T> *streamData;
                int streamSize;
                bool abilityToWrite;
                bool abilityToRead;
                bool abilityToSeek;
                bool abilityToTimeout;
                int creationTime;
                int timeout;
                std::string baseTypeOfSequense;
            public:
                Stream(bool, bool, bool, bool, int, std::string);
                Stream(Stream<T> &);
                Stream(T *, int, std::string);
                Stream(sequence::Sequence<T> *, std::string);
                bool canRead();
                bool canSeek();
                bool canWrite();
                bool canTimeout();
                void setAbilityToWrite(bool);
                void checkTimeout(bool = false);
                void setAbilityToRead(bool);
                void setAbilityToSeek(bool);
                void setAbilityToTimeout(bool);
                void setTimeout(int);
                bool empty();
                void push(T);
                void pop();
                void dispose();
                void *front();
                void *back();
                void swap(int, int);
                int size(std::string = "elements");
                Stream<T> &operator << (T);
                T operator >> (T &);
                Stream<T> &operator = (const Stream<T> &);
                Stream<T> operator + (const Stream<T> &);
                template<typename Iterator, typename castType> Iterator begin();
                template<typename Iterator, typename castType> Iterator end();
                template<typename T1>
                friend std::ostream &operator<<(std::ostream &, Stream<T1> &);
        };

        template<typename T>
        Stream<T>::Stream(bool abilityToWrite, bool abilityToRead, bool abilityToSeek, bool abilityToTimeout, int timeout, std::string baseTypeOfSequense) {
            this->abilityToWrite = abilityToWrite;
            this->abilityToRead = abilityToRead;
            this->abilityToSeek = abilityToSeek;
            this->abilityToTimeout = abilityToTimeout;
            this->timeout = timeout;
            this->creationTime = abilityToTimeout ? time(NULL) : -1;
            this->baseTypeOfSequense = baseTypeOfSequense;
            if (baseTypeOfSequense == "ArraySequence") {
                this->streamData = new arraySequence::ArraySequence<T>;
                this->streamSize = this->streamData->length();
            }
            else if (baseTypeOfSequense == "ListSequence") {
                this->streamData = new listSequence::ListSequence<T>;
                this->streamSize = this->streamData->length();
            }
            else {
                throw streamException::StreamException("Invalid type of base sequence!");
            }
        }

        template<typename T>
        bool Stream<T>::canRead() {
            checkTimeout();
            return this->abilityToRead;
        }

        template<typename T>
        bool Stream<T>::canSeek() {
            checkTimeout();
            return this->abilityToSeek;
        }

        template<typename T>
        bool Stream<T>::canWrite() {
            checkTimeout();
            return this->abilityToWrite;
        }

        template<typename T>
        bool Stream<T>::canTimeout() {
            checkTimeout();
            return abilityToTimeout;
        }

        template<typename T>
        void Stream<T>::checkTimeout(bool showTheRemainingTime) {
            if (this->abilityToTimeout && (time(NULL) - this->creationTime > this->timeout)) {
                dispose();
                throw streamException::StreamException("Timeout error!");
            }
            else {
                if (showTheRemainingTime){
                    std::cout << this->timeout - (time(NULL) - this->creationTime) << "seconds left...";
                }
            }
        }

        template<typename T>
        void Stream<T>::setAbilityToWrite(bool val) {
            checkTimeout();
            this->abilityToWrite = val;
        }

        template<typename T>
        void Stream<T>::setAbilityToRead(bool val) {
            checkTimeout();
            this->abilityToRead = val;
        }

        template<typename T>
        void Stream<T>::setAbilityToSeek(bool val) {
            checkTimeout();
            this->abilityToSeek = val;
        }

        template<typename T>
        void Stream<T>::setAbilityToTimeout(bool val) {
            checkTimeout();
            this->abilityToTimeout = val;
        }

        template<typename T>
        void Stream<T>::setTimeout(int val) {
            checkTimeout();
            this->timeout = val;
        }

        template<typename T>
        void Stream<T>::push(T val) {
            if (this->abilityToWrite) {
                checkTimeout();
                this->streamData->prepend(val);
                ++this->streamSize;
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T1>
        std::ostream &operator<<(std::ostream &out, Stream<T1> &St) {
            St.checkTimeout();
            if (St.abilityToRead) {
                if (!St.empty()){
                    for (int i = 0; i < St.streamSize; ++i) {
                        if (i == St.streamSize - 1){
                            out << St.streamData->getElement(i);
                        }
                        else {
                            out << St.streamData->getElement(i) << "->";
                        }
                    }
                }
                else {
                    out << "NULL";
                }
            }
            else {
                throw streamException::StreamException("Read error!");
            }
            return out;
        }

        template<typename T>
        bool Stream<T>::empty() {
            checkTimeout();
            return this->streamSize == 0;
        }

        template<typename T>
        void Stream<T>::pop() {
            if(this->abilityToWrite){
                checkTimeout();
                this->streamData->pop(this->streamSize - 1);
                --this->streamSize;
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        void Stream<T>::dispose() {
            checkTimeout();
            if (this->abilityToWrite) {
                while (this->streamSize != 0) {
                    pop();
                }
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        Stream<T>::Stream(Stream<T> &St) {
            this->abilityToWrite = St.abilityToWrite;
            this->abilityToRead = St.abilityToRead;
            this->abilityToSeek = St.abilityToSeek;
            this->abilityToTimeout = St.abilityToTimeout;
            this->timeout = St.timeout;
            this->creationTime = St.creationTime;
            this->baseTypeOfSequense = St.baseTypeOfSequense;
            this->streamSize = St.streamSize;
            if (this->baseTypeOfSequense == "ArraySequence") {
                this->streamData = new arraySequence::ArraySequence<T>;
                for (int i = 0; i < this->streamSize; ++i){
                    this->streamData->append(St.streamData->getElement(i));
                }
            }
            else if (this->baseTypeOfSequense == "ListSequence") {
                this->streamData = new listSequence::ListSequence<T>;
                for (int i = 0; i < this->streamSize; ++i){
                    this->streamData->append(St.streamData->getElement(i));
                }
            }
            else {
                throw streamException::StreamException("Invalid type of base sequence!");
            }
        }

        template<typename T>
        Stream<T>::Stream(T *mas, int n, std::string baseTypeOfSequense) {
            this->abilityToWrite = true;
            this->abilityToRead = true;
            this->abilityToSeek = true;
            this->abilityToTimeout = false;
            this->timeout = -1;
            this->creationTime = abilityToTimeout ? time(NULL) : -1;
            this->baseTypeOfSequense = baseTypeOfSequense;
            if (baseTypeOfSequense == "ArraySequence") {
                this->streamData = new arraySequence::ArraySequence<T>;
                this->streamSize = this->streamData->length();
            }
            else if (baseTypeOfSequense == "ListSequence") {
                this->streamData = new listSequence::ListSequence<T>;
                this->streamSize = this->streamData->length();
            }
            else {
                throw streamException::StreamException("Invalid type of base sequence!");
            }
            if (this->abilityToWrite){
                for (int i = 0; i < n; ++i){
                    this->streamData->prepend(mas[i]);
                    ++this->streamSize;
                }
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        Stream<T>::Stream(sequence::Sequence<T> *Seq, std::string baseTypeOfSequense) {
            this->abilityToWrite = true;
            this->abilityToRead = true;
            this->abilityToSeek = true;
            this->abilityToTimeout = false;
            this->timeout = -1;
            this->creationTime = abilityToTimeout ? time(NULL) : -1;
            this->baseTypeOfSequense = baseTypeOfSequense;
            if (baseTypeOfSequense == "ArraySequence") {
                this->streamData = new arraySequence::ArraySequence<T>;
                this->streamSize = this->streamData->length();
            }
            else if (baseTypeOfSequense == "ListSequence") {
                this->streamData = new listSequence::ListSequence<T>;
                this->streamSize = this->streamData->length();
            }
            else {
                throw streamException::StreamException("Invalid type of base sequence!");
            }
            if (this->abilityToWrite){
                for (int i = 0; i < Seq->length(); ++i){
                    this->streamData->prepend(Seq->getElement(i));
                    ++this->streamSize;
                }
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        void *Stream<T>::front() {
            checkTimeout();
            if (this->abilityToSeek){
                return this->streamData->getLast();
            }
            else {
                throw streamException::StreamException("Seek error!");
            }
        }

        template<typename T>
        void *Stream<T>::back() {
            checkTimeout();
            if (this->abilityToSeek){
                return this->streamData->getFirst();
            }
            else {
                throw streamException::StreamException("Seek error!");
            }
        }

        template<typename T>
        void Stream<T>::swap(int index1, int index2) {
            checkTimeout();
            if (this->abilityToWrite){
                if (index1 >= 0 && index2 >= 0 && index1 < this->streamSize && index2 < this->streamSize) {
                    this->streamData->swap(index1, index2);
                }
                else {
                    throw streamException::StreamException("Index out of range!");
                }
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        int Stream<T>::size(std::string param) {
            checkTimeout();
            if (param == "bites") {
                if (this->streamSize == 0){
                    return 0;
                }
                else {
                    return this->streamSize  * sizeof(this->streamData->getElement(0)) * 8;
                }
            }
            else if (param == "elements") {
                return this->streamSize;
            }
            else {
                throw streamException::StreamException("Incorrect param!");
            }
        }

        template<typename T>
        Stream<T> &Stream<T>::operator<<(T val) {
            checkTimeout();
            if (this->abilityToWrite) {
                push(val);
                return *this;
            }
            else {
                throw streamException::StreamException("Write error!");
            }
        }

        template<typename T>
        T Stream<T>::operator>>(T &val) {
            checkTimeout();
            if (this->abilityToSeek) {
                val = this->streamData->getElement(this->streamSize - 1);
                pop();
                return val;
            }
            else {
                throw streamException::StreamException("Seek error!");
            }
        }

        template<typename T>
        Stream<T> &Stream<T>::operator=(const Stream<T> &St) {
            checkTimeout();
            if (this == &St){
                return *this;
            }
            dispose();
            this->abilityToWrite = St.abilityToWrite;
            this->abilityToRead = St.abilityToRead;
            this->abilityToSeek = St.abilityToSeek;
            this->abilityToTimeout = St.abilityToTimeout;
            this->timeout = St.timeout;
            this->creationTime = St.creationTime;
            this->baseTypeOfSequense = St.baseTypeOfSequense;
            this->streamSize = St.streamSize;
            if (this->baseTypeOfSequense == "ArraySequence") {
                this->streamData = new arraySequence::ArraySequence<T>;
                for (int i = 0; i < this->streamSize; ++i){
                    this->streamData->append(St.streamData->getElement(i));
                }
            }
            else if (this->baseTypeOfSequense == "ListSequence") {
                this->streamData = new listSequence::ListSequence<T>;
                for (int i = 0; i < this->streamSize; ++i){
                    this->streamData->append(St.streamData->getElement(i));
                }
            }
            else {
                throw streamException::StreamException("Invalid type of base sequence!");
            }
            return *this;
        }

        template<typename T>
        Stream<T> Stream<T>::operator+(const Stream<T> &St) {
            checkTimeout();
            Stream<T> BuffSt(*this);
            for (int i = St.streamSize - 1; i >= 0; --i){
                BuffSt.push(St.streamData->getElement(i));
            }
            return BuffSt;
        }

        template<typename T>
        template<typename Iterator, typename castType>
        Iterator Stream<T>::begin() {
            checkTimeout();
            return dynamic_cast<castType>(this->streamData)->begin();
        }

        template<typename T>
        template<typename Iterator, typename castType>
        Iterator Stream<T>::end() {
            checkTimeout();
            return dynamic_cast<castType>(this->streamData)->end();
        }

    }
#endif
