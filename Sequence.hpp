#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <functional>
#include <iostream>

using namespace std;

template<typename Type>
using Mapper = Type(*)(Type &);

template<typename Type>
using Condition = bool (*)(Type &);

template<typename Type>
using Reducer = Type(*)(Type &, Type &);

template<typename Type>
class Sequence {
public:
    virtual ~Sequence() {};

    virtual Sequence<Type> *Create() const = 0;

    virtual Type &Get(int index) const = 0;

    virtual int Size() const noexcept = 0;

    virtual void Append(const Type &item) noexcept = 0;

    virtual void Prepend(const Type &item) noexcept = 0;

    virtual void Insert(const Type &item, int index) = 0;

    virtual void Remove(int index) = 0;     // переопределяется в list и array

    bool IsEmpty() { return this->Size() == 0; }

    Type &GetFirst() const {
        if (this->IsEmpty()) throw out_of_range("Index out of range");
        return Get(0);
    };

    Type &GetLast() const {
        if (this->IsEmpty()) throw out_of_range("Index out of range");
        int last = this->Size() - 1;
        return this->Get(last);
    };

    Sequence<Type> *Map(Mapper<Type> func) const {
        Sequence<Type> *result = this->Create();
        for (size_t i = 0; i < this->Size(); i++) result->Append(func(this->Get(i)));
        return result;
    }

    Sequence<Type> *Where(Condition<Type> filter) const {
        Sequence<Type> *result = this->Create();
        for (size_t i = 0; i < this->Size(); i++) {
            if (filter(this->Get(i))) result->Append(this->Get(i));
        }
        return result;
    }

    Type Reduce(Reducer<Type> reduce, Type base) const {
        for (size_t i = 0; i < Size(); i++) base = reduce(Get(i), base);
        return base;
    }

    friend ostream &operator<<(ostream &os, Sequence<Type> *array) {
        if (array->Size() == 0) os << "[]";
        else {
            os << "[";
            for (size_t i = 0; i < array->Size() - 1; i++) os << array->Get(i) << ", ";
            os << array->Get(array->Size() - 1) << "]";
        }
        return os;
    }

    bool operator==(const Sequence<Type> &sequence) {
        if (this->Size() != sequence.Size()) return false;
        for (int i = 0; i < this->Size(); i++) if (this->Get(i) != sequence.Get(i)) return false;
        return true;
    }

    Type &operator[](const int index) const { return this->Get(index); }
};


#endif //SEQUENCE_HPP