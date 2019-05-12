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
template<class T>void Container<T>::push(T& data) {
    head->next = new Node{&data, head->next};
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
        if (f(cur)) return cur->data;
    } while (cur->next);

    return nullptr;
}
template<class T>void Container<T>::sort(Fcompare f) {
    if (!head->next || !head->next->next) return;
    T *ceil = nullptr, *lastSorted;
    bool isSorted;

    do {
        isSorted = true;
        lastSorted = head;
        for (T *cur = head; cur->next->next != ceil; cur = cur->next) {
            std::cout << "   Items compared: " << cur->next->data->getSurname() << ", " << cur->next->next->data->getSurname();
            if (f(*cur->next->data, *cur->next->next->data) > 0) {
                swapAdjacentNodes(cur);
                lastSorted = cur;
                isSorted = false;
                std::cout << " => swapped\n";
            } else {
                std::cout << " => not swapped\n";
            }
        }
        ceil = lastSorted;
        std::cout << "Iteration (ceil=" << std::string(*ceil->data) << ")\n";
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
