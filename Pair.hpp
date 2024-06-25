#ifndef MOSQUITO_MORON_PAIR_HPP
#define MOSQUITO_MORON_PAIR_HPP

#include <iostream>

using namespace std;

template<typename Type1, typename Type2>
class Pair {
private:
    Type1 first;
    Type2 last;
public:
    Pair() : first(Type1()), last(Type2()) {}

    Pair(const Type1 &val1, const Type2 &val2) : first(val1), last(val2) {}

    Pair(const Pair<Type1, Type2> &other) : first(other.first), last(other.last) {}

    ~Pair() = default;

    Type1 GetFirst() const noexcept { return first; }

    Type2 GetLast() const noexcept { return last; }

    Pair<Type1, Type2> &operator=(const Pair<Type1, Type2> &other) {
        this->first = other.first;
        this->last = other.last;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Pair<Type1, Type2> &pair) {
        os << "(";
        os << pair.first;
        os << ", ";
        os << pair.last;
        os << ")";
        return os;
    }
};

#endif //MOSQUITO_MORON_PAIR_HPP