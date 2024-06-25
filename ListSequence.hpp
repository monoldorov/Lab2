#ifndef MOSQUITO_MORON_LISTSEQUENCE_HPP
#define MOSQUITO_MORON_LISTSEQUENCE_HPP

#include "Sequence.hpp"
#include "List.hpp"

template<typename Type>
class ListSequence : public Sequence<Type> {
private:
    LinkedList<Type> *items;
public:
    ListSequence() : items(new LinkedList<Type>()) {}

    ListSequence(Type *items, size_t size) : items(new LinkedList<Type>(items, size)) {}

    ListSequence(const ListSequence<Type> &listSequence) : items(new LinkedList<Type>(listSequence)) {}

    template<typename... Args>
    explicit ListSequence(Type head, Args... args) : items(new LinkedList<Type>(head, args...)) {}

    virtual ~ListSequence() { delete items; }

    using Iterator = typename LinkedList<Type>::ListIterator;

    Iterator Begin() { return items->Begin(); }

    Iterator End() { return items->End(); }

    Sequence<Type> *Create() const override { return (Sequence<Type> *) new ListSequence<Type>(); }

    Type &Get(int index) const override { return this->items->Get(index); };

    int Size() const noexcept override { return this->items->Size(); }

    void Append(const Type &item) noexcept override { this->items->Append(item); }

    void Prepend(const Type &item) noexcept override { this->items->Prepend(item); }

    void Insert(const Type &item, int index) override {
        if (index < 0 || index > this->Size()) throw out_of_range("Index out of range");
        this->items->Insert(index, item);
    }

    void Remove(int index) override { this->items->Remove(index); }
};

#endif //MOSQUITO_MORON_LISTSEQUENCE_HPP
