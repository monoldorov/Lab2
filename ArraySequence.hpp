#ifndef MOSQUITO_MORON_ARRAYSEQUENCE_HPP
#define MOSQUITO_MORON_ARRAYSEQUENCE_HPP

#include "Sequence.hpp"
#include "DynamicArray.hpp"

using namespace std;

template<typename Type>
class ArraySequence : public Sequence<Type> {
private:
    DynamicArray<Type> *items;
public:
    ArraySequence() : items(new DynamicArray<Type>()) {}

    ArraySequence(Type *items, size_t size) : items(new DynamicArray<Type>(items, size)) {}

    explicit ArraySequence(const DynamicArray<Type> &dynamicArray) : items(new DynamicArray<Type>(dynamicArray)) {}

    virtual ~ArraySequence() { delete items; }

    Sequence<Type> *Create() const override { return (Sequence<Type> *) new ArraySequence<Type>(); }

    Type &Get(int index) const override { return this->items->Get(index); };

    int Size() const noexcept override { return this->items->Size(); }

    void Append(const Type &item) noexcept override {
        int size = this->Size();
        this->items->Resize(size + 1);
        Set(size, item);
    }

    void Prepend(const Type &item) noexcept override {
        int size = this->Size();
        this->items->Resize(size + 1);
        for (int i = size; i > 0; i--) Set(i, Get(i - 1));
        Set(0, item);
    }

    void Insert(const Type &item, int index) override {
        if (index < 0 || index > this->Size()) throw out_of_range("Index out of range");

        if (index == 0) {
            Prepend(item);
            return;
        }

        int size = this->Size();
        if (index == size) {
            Append(item);
            return;
        }
        this->items->Resize(size + 1);
        for (int i = size; i > index; i--) Set(i, Get(i - 1));
        Set(index, item);
    }

    void Remove(int index) override {
        int size = this->Size();
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        for (int i = index; i > size - 1; i++) Set(i, Get(i + 1));
        this->items->Resize(size + 1);
    }

    void Set(int index, Type value) { this->items->Set(index, value); }
};

#endif //MOSQUITO_MORON_ARRAYSEQUENCE_HPP