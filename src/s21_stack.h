//
// Created by Tandra Ymir on 8/1/23.
//

#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H

// #include "s21_list.h"
// #include "s21_vector.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
 public:
  using container_type = Container;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack() : head_() {}

  explicit stack(std::initializer_list<value_type> const &items) {
    for (value_type i : items) {
      head_.push_back(i);
    }
  }

  stack(const stack &other) : head_(other.head_) {}

  stack(stack &&other) : head_(std::move(other.head_)) {}

  ~stack() {}

  stack &operator=(stack &&other) {
    head_ = std::move(other.head_);
    return *this;
  }

  stack &operator=(const stack &other) {
    head_ = other.head_;
    return *this;
  }

  const_reference top() { return head_.back(); }

  bool empty() { return head_.empty(); }

  size_type size() { return head_.size(); }

  void push(const_reference value) { head_.push_back(value); }

  void pop() { head_.pop_back(); }

  void swap(stack &other) { head_.swap(other.head_); }

 private:
  container_type head_;
};
}  // namespace s21
#endif  // CONTAINERS_STACK_H
