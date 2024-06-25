#ifndef MOSQUITO_MORON_DYNAMICARRAY_HPP
#define MOSQUITO_MORON_DYNAMICARRAY_HPP

#include <functional>
#include <iostream>

using namespace std;

template<typename Type>
class DynamicArray {
private:
    Type *data;
    size_t size;
public:
    DynamicArray() : size(0), data(new Type[1]) { data[0] = Type(); }

    explicit DynamicArray(size_t size) : size(size), data(new Type[size]) {
        for (int i = 0; i < size; i++) data[i] = Type();
    }

    DynamicArray(Type *items, size_t size) : size(size), data(new Type[size]) {
        for (int i = 0; i < size; i++) data[i] = items[i];
    }

    DynamicArray(const DynamicArray<Type> &dynamicArray) : size(dynamicArray.size), data(new Type[size]) {
        for (int i = 0; i < size; i++) { data[i] = dynamicArray.data[i]; }
    }

    template<typename... Args>
    explicit DynamicArray(Type head, Args... args) {
        data = new Type[sizeof...(args) + 1];
        data[0] = head;

        size = sizeof...(args) + 1;

        size_t i = 1;
        ((data[i++] = args), ...);
    }

    ~DynamicArray() { delete[] data; }

    void Resize(size_t newSize) {
        Type *newBlock = new Type[newSize];
        for (size_t i = 0; i < newSize; i++) newBlock[i] = Type();

        if (newSize < size) for (size_t i = 0; i < newSize; i++) newBlock[i] = this->Get(i);
        else for (size_t i = 0; i < size; i++) newBlock[i] = this->Get(i);

        delete[] data;

        data = newBlock;
        size = newSize;
    }

    Type &Get(int index) const {
        if (index >= size || index < 0) throw out_of_range("Index out of range");
        return data[index];
    }

    void Set(int index, Type element) {
        if (index >= size || index < 0) throw out_of_range("Index out of range");
        data[index] = element;
    }

    int Size() const noexcept { return size; }

    friend ostream &operator<<(ostream &os, const DynamicArray<Type> &array) {
        if (array.size == 0) os << "[]";
        else {
            os << "[";
            for (size_t i = 0; i < array.size - 1; i++) os << array.Get(i) << ", ";
            os << array.Get(array.size - 1) << "]";
        }
        return os;
    }

    bool operator==(const DynamicArray<Type> &sequence) {
        if (this->size != sequence.GetLength()) return false;
        for (int i = 0; i < this->size; i++) if (this->Get(i) != sequence.Get(i)) return false;
        return true;
    }

    auto &operator[](const int index) const { return Get(index); }
};


#endif //MOSQUITO_MORON_DYNAMICARRAY_HPP