// Shymanovych Vladyslav
#pragma once
#include "Container.h"

template<class T>Container<T>::Container() {
    head = new Node{nullptr, nullptr};
}
template<class T>sizetype Container<T>::size() const noexcept { return count; }
template<class T>bool Container<T>::empty() const noexcept { return size() == 0; }
template<class T>void Container<T>::clear() {
    while (!empty())
        pop();
}
template<class T>void Container<T>::push(T* data) {
    head->next = new Node{data, head->next};
    ++count;
}
template<class T>void Container<T>::pop() {
    throwIfEmpty("Unable to pop, no elements left");
    Node* tmp = head->next->next;
    delete head->next;
    head->next = tmp;
    --count;
}
template<class T>const T& Container<T>::top() const {
    throwIfEmpty("Unable to access the element, no elements left");
    return head->next->data;
}
template<class T>T& Container<T>::top() {
    throwIfEmpty("Unable to access the element, no elements left");
    return *head->next->data;
}

template<class T>T* Container<T>::find(Fmatch f) {
    if (empty()) return nullptr;
    Node *cur = head;

    do {
        cur = cur->next;
        if (f(*(cur->data))) return cur->data;
    } while (cur->next);

    return nullptr;
}
template<class T>void Container<T>::sort(Fcompare f) {
    bool isSorted;
    size_t ceil = size()-1, last = 0;
    Node* cur;

    do {
        isSorted = true;
        last = 0;
        cur = head;
        for (size_t i = 0; i < ceil; cur = cur->next, ++i) {
            if (f(*cur->next->data, *cur->next->next->data) > 0) {
                swapAdjacentNodes(cur);
                last = i;
                isSorted = false;
            }
        }
        ceil = last;
    } while (!isSorted);
}
template<class T>void Container<T>::swapAdjacentNodes(Node* prev) {
    Node *A = prev->next;
    prev->next = A->next;
    A->next = prev->next->next;
    prev->next->next = A;
}

template<class T>void Container<T>::throwIfEmpty(const std::string& msg) const {
    if (empty()) throw std::out_of_range(msg);
}

template<class T> Container<T>::operator std::string() const {
    std::string s;
    for (Node *cur = head->next; cur != nullptr; cur = cur->next) {
        s += "- " + std::string(*(cur->data)) + "\n";
    }
    return s;
}



template<class T> Container<T>::Iterator::Iterator(Node* node) {
    cur = node;
}
template<class T> typename Container<T>::Iterator& Container<T>::Iterator::operator ++ () {
    if (cur) cur = cur->next;
    return *this;
}
template<class T> T* Container<T>::Iterator::operator * () const {
    // if (!cur) throw std::out_of_range("Unable to access the element, invalid pointer");
    return cur->data;
}
template<class T> bool Container<T>::Iterator::operator != (const Iterator& other) const noexcept {
    return this->cur != other.cur;
}

template<class T> typename Container<T>::Iterator Container<T>::begin() const noexcept { return Iterator(head->next); }
template<class T> typename Container<T>::Iterator Container<T>::end() const noexcept { return Iterator(); }

template<class T> void Container<T>::iterate(FIteration f) {
    Iterator i = begin(), i_end = end();
    for (; i != i_end; ++i) {
        f(**i);
    }
}
