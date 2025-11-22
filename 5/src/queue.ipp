#include "queue.h"


template <typename T>
Queue<T>::Queue(std::pmr::memory_resource* res)
    : alloc_(res), head_(nullptr), tail_(nullptr), sz_(0) {}

template <typename T>
Queue<T>::Queue(const Queue& other)
    : alloc_(other.alloc_.resource()), head_(nullptr), tail_(nullptr), sz_(0) {
    for (Node* cur = other.head_; cur != nullptr; cur = cur->next_) {
        Push(cur->val_);
    }
}

template <typename T>
Queue<T>::Queue(Queue&& other) noexcept
    : alloc_(other.alloc_.resource()), head_(other.head_), tail_(other.tail_), sz_(other.sz_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.sz_ = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        Clear();
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next_) {
            Push(cur->val_);
        }
    }
    return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        Clear();
        head_ = other.head_;
        tail_ = other.tail_;
        sz_ = other.sz_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.sz_ = 0;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    Clear();
}

template <typename T>
void Queue<T>::Push(const T& value) {
    Node* node = alloc_.allocate(1);
    alloc_.construct(node, value);
    if (tail_) {
        tail_->next_ = node;
    } else {
        head_ = node;
    }
    tail_ = node;
    ++sz_;
}

template <typename T>
void Queue<T>::Push(T&& value) {
    Node* node = alloc_.allocate(1);
    alloc_.construct(node, std::move(value));
    if (tail_) {
        tail_->next_ = node;
    } else {
        head_ = node;
    }
    tail_ = node;
    ++sz_;
}

template <typename T>
void Queue<T>::Pop() {
    if (IsEmpty()) {
        throw ListIsEmptyException("Queue is empty!");
    }
    Node* del = head_;
    head_ = head_->next_;
    std::destroy_at(del);
    alloc_.deallocate(del, 1);
    --sz_;
    if (!head_) tail_ = nullptr;
}

template <typename T>
T& Queue<T>::Front() {
    if (IsEmpty()) throw ListIsEmptyException("Queue is empty!");
    return head_->val_;
}

template <typename T>
T& Queue<T>::Back() {
    if (IsEmpty()) throw ListIsEmptyException("Queue is empty!");
    return tail_->val_;
}

template <typename T>
const T& Queue<T>::Front() const {
    if (IsEmpty()) throw ListIsEmptyException("Queue is empty!");
    return head_->val_;
}

template <typename T>
const T& Queue<T>::Back() const {
    if (IsEmpty()) throw ListIsEmptyException("Queue is empty!");
    return tail_->val_;
}

template <typename T>
bool Queue<T>::IsEmpty() const noexcept {
    return sz_ == 0;
}

template <typename T>
size_t Queue<T>::Size() const noexcept {
    return sz_;
}

template <typename T>
void Queue<T>::Clear() noexcept {
    while (head_) {
        Node* next = head_->next_;
        std::destroy_at(head_);
        alloc_.deallocate(head_, 1);
        head_ = next;
    }
    tail_ = nullptr;
    sz_ = 0;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Begin() const noexcept {
    return Iterator(head_);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::End() const noexcept {
    return Iterator(nullptr);
}