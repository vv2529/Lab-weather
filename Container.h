// Shymanovych Vladyslav
#pragma once
#include <functional>
#include <cstdlib>
#include <iostream>

using sizetype = std::size_t;
// ...nodes...<-head
// head is empty
template<class T> class Container {

    using Fmatch = std::function<bool (const T&)>;// bool(*) (const T&);
    using Fcompare = std::function<short (const T&, const T&)>;// short(*) (const T&, const T&);

public:
    Container();
    Container(const Container&) = delete;
    Container(Container&&) = delete;
    Container& operator = (const Container&) = delete;
    Container& operator = (Container&&) = delete;
    sizetype size() const noexcept;
    bool empty() const noexcept;
    void clear();
    void push(T*);
    void pop();
    const T& top() const;
    T& top();
    T* find(Fmatch); // return null if not found; starts from head
    void sort(Fcompare); // bubble sort
protected:
    struct Node {
        T* data;
        Node* next;
    };
    Node *head = nullptr;
    sizetype count = 0;

    void throwIfEmpty(const std::string&) const;
    void swapAdjacentNodes(Node* prev);
};
#include "Container.cpp"
