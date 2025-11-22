
#pragma once

#include <cstdlib>
#include <functional>
#include <iterator>
#include <memory_resource>
#include <utility>

#include "exceptions.h"

template <typename T>
class Queue {
private:
    struct Node {
        T val_;
        Node* next_;
        Node(const T& val) : val_(val), next_(nullptr) {}
        Node(T&& val) : val_(std::move(val)), next_(nullptr) {}
    };

    std::pmr::polymorphic_allocator<Node> alloc_;
    Node* head_;
    Node* tail_;
    size_t sz_;

public:
    class Iterator {
        Node* current_;
    public:
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(Node* node) : current_(node) {}
        bool operator==(const Iterator& other) const { return current_ == other.current_; }
        bool operator!=(const Iterator& other) const { return current_ != other.current_; }
        reference operator*() const { return current_->val_; }
        pointer operator->() const { return std::addressof(current_->val_); }
        Iterator& operator++() { current_ = current_->next_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
    };

    Queue(std::pmr::memory_resource* res = std::pmr::get_default_resource());
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    ~Queue();

    void Push(const T& value);
    void Push(T&& value);
    void Pop();
    T& Front();
    T& Back();
    const T& Front() const;
    const T& Back() const;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    void Clear() noexcept;

    Iterator Begin() const noexcept;
    Iterator End() const noexcept;
};


#include "queue.ipp"