#ifndef MOSQUITO_MORON_QUEUEWITHPRIORITY_HPP
#define MOSQUITO_MORON_QUEUEWITHPRIORITY_HPP

#include "Sequence.hpp"
#include "ListSequence.hpp"
#include "Pair.hpp"

using namespace std;

template<typename Type1, typename Type2>
class PriorityQueue {
private:
    Sequence<Pair<Type1, Type2>> *items;
public:
    PriorityQueue() : items(new ListSequence<Pair<Type1, Type2>>()) {}

    PriorityQueue(Pair<Type1, Type2> *items, size_t size) : items(new ListSequence<Pair<Type1, Type2>>(items, size)) {}

    PriorityQueue(const PriorityQueue<Type1, Type2> &queue) : items(new ListSequence<Pair<Type1, Type2>>()) {
        for (int i = 0; i < queue.Size(); i++) this->InsertWithPriority(queue.Peek(i));
    }

    ~PriorityQueue() {}

    const Pair<Type1, Type2> &Peek(int ind) const { return this->items->Get(ind); }

    int Size() const noexcept { return this->items->Size(); }

    void Insert(const Type1 &item, int index) { this->items->Insert(item, index); }

    void InsertWithPriority(Pair<Type1, Type2> value) noexcept {
        int i = 0;
        int len = this->Size();
        for (i; i < len; i++) if (value.GetLast() < this->Peek(i).GetLast()) break;
        this->Insert(value, i);
    }

    PriorityQueue<Type1, Type2> concatWithPriority(const PriorityQueue<Type1, Type2> &queue) {
        auto copy = queue;
        int len = this->Size();
        for (int i = 0; i < len; i++) copy.InsertWithPriority(this->Peek(i));
        return copy;
    }

    friend ostream &operator<<(ostream &os, const PriorityQueue<Type1, Type2> &queue) {
        os << queue.items;
        return os;
    }
};

#endif //MOSQUITO_MORON_QUEUEWITHPRIORITY_HPP