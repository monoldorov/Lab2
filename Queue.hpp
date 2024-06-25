#ifndef MOSQUITO_MORON_QUEUE_HPP
#define MOSQUITO_MORON_QUEUE_HPP

#include "ListSequence.hpp"

using namespace std;

template<typename Type>
using Mapper = Type(*)(Type &);

template<typename Type>
using Condition = bool (*)(Type &);

template<typename Type>
using Reducer = Type(*)(Type &, Type &);

template<typename Type>
class Queue {
private:
    Sequence<Type> *items;
public:
    Queue() : items(new ListSequence<Type>()) {}

    Queue(Type *items, size_t size) : items(new ListSequence<Type>(items, size)) {}

    Queue(const Queue<Type> &queue) : items(queue.items->Create()) {
        for (int i = 0; i < queue.Size(); i++) this->Append(queue.Peek(i));
    }

    explicit Queue(const Sequence<Type> *sequence) : items(sequence->Create()) {
        for (int i = 0; i < sequence->Size(); i++) this->items->Append(sequence->Get(i));
    }

    template<typename... Args>
    explicit Queue(Type head, Args... args)  : items(new ListSequence<Type>(head, args...)) {}

    ~Queue() { delete items; }

    const Type &Peek(size_t index) const { return this->items->Get(index); }

    size_t Size() const noexcept { return this->items->Size(); }

    void Append(const Type &val) noexcept { this->items->Append(val); }

    Type Remove() {
        Type first = this->items->GetFirst();
        this->items->Remove(0);
        return first;
    }

    bool IsEmpty() const noexcept { return this->items->IsEmpty(); }

    Queue<Type> Map(Mapper<Type> func) {
        auto copy = this->items->Map(func);
        Queue<Type> res = copy;
        delete copy;
        return res;

    }

    Queue<Type> Where(Condition<Type> filter) {
        auto copy = this->items->Where(filter);
        Queue<Type> res = copy;
        delete copy;
        return res;
    }

    Type Reduce(Reducer<Type> reduce, Type base) const { return this->items->Reduce(reduce, base); }

    friend ostream &operator<<(ostream &os, const Queue<Type> &queue) {
        os << queue.items;
        return os;
    }
};

#endif //MOSQUITO_MORON_QUEUE_HPP
