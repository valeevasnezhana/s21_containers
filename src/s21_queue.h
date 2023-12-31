// Copyright 2023 School21 @tandraym
#ifndef CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() : head_() {}

  explicit queue(std::initializer_list<value_type> const &items) {
    for (value_type i : items) {
      head_.push_back(i);
    }
  }

  queue(const queue &other) : head_(other.head_) {}

  queue(queue &&other) : head_(std::move(other.head_)) {}

  ~queue() {}

  queue &operator=(queue &&other) noexcept {
    head_ = std::move(other.head_);
    return *this;
  }

  queue &operator=(const queue &other) {
    head_ = other.head_;
    return *this;
  }

  const_reference front() { return head_.front(); }
  const_reference back() { return head_.back(); }

  bool empty() { return head_.empty(); }

  size_type size() { return head_.size(); }

  void push(const_reference value) { head_.push_back(value); }

  void pop() { head_.pop_front(); }

  void swap(queue &other) { head_.swap(other.head_); }

 private:
  s21::list<T> head_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
