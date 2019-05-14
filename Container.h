// Shymanovych Vladyslav
#pragma once
#include <functional>
#include <cstdlib>
#include <iostream>
#include <string>

using sizetype = std::size_t;
// ...nodes...<-head
// head is empty
template<class T> class Container {
public:
    using Fmatch = std::function<bool (const T&)>;// bool(*) (const T&);
    using Fcompare = std::function<short (const T&, const T&)>;// short(*) (const T&, const T&);
    using FIteration = std::function<void (T&)>;
    using FIterationConst = std::function<void (const T&)>;

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
    void sort(Fcompare f =
        [] (const T& a, const T& b) -> short {
            if (a < b) return -1;
            if (a > b) return 1;
            return 0;
        }
    ); // bubble sort
    operator std::string() const;
protected:
    struct Node {
        T* data;
        Node* next;
    };
    Node *head = nullptr;
    sizetype count = 0;

    void throwIfEmpty(const std::string&) const;
    void swapAdjacentNodes(Node* prev);
public:
    class Iterator {
    public:
        Iterator(Node* = nullptr);
        Iterator& operator ++ ();
        T* operator * () const;
        bool operator != (const Iterator&) const noexcept;
        Node* cur;
    };
    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    void iterate(FIteration);
};
#include "Container.cpp"
