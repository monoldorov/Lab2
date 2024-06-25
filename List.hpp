#ifndef MOSQUITO_MORON_LIST_HPP
#define MOSQUITO_MORON_LIST_HPP

#include <iostream>

using namespace std;

template<typename Type>
class Node {
public:
    Type value;
    Node<Type> *next;

    explicit Node(Type value) : value(value), next(nullptr) {}
};


template<typename Type>
class LinkedList {
private:
    Node<Type> *head = nullptr;
    Node<Type> *tail = nullptr;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(Type *items, size_t size) : head(nullptr), tail(nullptr), size(0) {
        for (int i = 0; i < size; i++) Append(items[i]);
    }

    LinkedList(const LinkedList<Type> &linkedList) : head(nullptr), tail(nullptr), size(0) {
        for (int i = 0; i < linkedList.size; i++) {
            Type val = linkedList.Get(i);
            Append(val);
        }
    }

    template<typename... Args>
    explicit LinkedList(Type head, Args... args) : head(nullptr), tail(nullptr), size(0) {
        this->Append(head);
        ((this->Append(args)), ...);
    }

    ~LinkedList() {
        Node<Type> *current = head;
        while (current != nullptr) {
            Node<Type> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    class ListIterator {
    private:
        Node<Type> *current;
    public:
        ListIterator() : current(nullptr) {}

        explicit ListIterator(Node<Type> *node) : current(node) {}

        ListIterator &operator++() {
            current = current->next;
            return *this;
        }

        Type &operator*() const { return current->value; }

        bool operator==(const ListIterator &other) const { return this->current == other.current; }

        bool operator!=(const ListIterator &other) const { return this->current != other.current; }
    };

    ListIterator Begin() { return ListIterator(this->head); }

    ListIterator End() { return ListIterator(nullptr); }

    bool IsEmpty() const noexcept { return size == 0; }

    Type &Get(int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node<Type> *current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->value;
    }

    size_t Size() const noexcept { return size; }

    void Append(const Type &value) noexcept {
        auto *node = new Node<Type>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void Prepend(const Type &value) noexcept {
        auto *node = new Node<Type>(value);
        node->next = head;
        head = node;
        if (tail == nullptr) tail = node;
        size++;
    }

    void Insert(int index, const Type &value) {
        if (index < 0 || index > size) throw out_of_range("Index out of range");
        if (index == 0) Prepend(value);
        else if (index == size) Append(value);
        else {
            Node<Type> *current = head;
            for (int i = 0; i < index - 1; i++) current = current->next;
            auto *node = new Node<Type>(value);
            node->next = current->next;
            current->next = node;
            size++;
        }
    }

    void Remove(int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        if (index == 0) {
            Node<Type> *temp = head;
            head = head->next;
            if (tail == temp) tail = nullptr;
            delete temp;
        }
        else {
            Node<Type> *current = head;
            for (int i = 0; i < index - 1; i++) current = current->next;
            Node<Type> *temp = current->next;
            current->next = temp->next;
            if (tail == temp) tail = current;
            delete temp;
        }
        size--;
    }

    Type &GetFirst() const {
        if (this->IsEmpty()) throw out_of_range("Index out of range");
        return head->value;
    }

    Type &GetLast() const {
        if (this->IsEmpty()) throw out_of_range("Index out of range");
        return tail->value;
    }

    friend ostream &operator<<(ostream &os, const LinkedList &list) {
        if (list.IsEmpty()) os << "[]";
        else {
            os << "[";
            for (size_t i = 0; i < list.size - 1; i++) os << list.Get(i) << ", ";
            os << list.Get(list.size - 1) << "]";
        }
        return os;
    }

    bool operator==(const LinkedList<Type> &list) {
        if (this->size != list.len()) return false;
        for (int i = 0; i < this->size; i++) if (this->Get(i) != list.Get(i)) return false;
        return true;
    }

    auto &operator[](const int index) const { return Get(index); }
};

#endif //MOSQUITO_MORON_LIST_HPP
