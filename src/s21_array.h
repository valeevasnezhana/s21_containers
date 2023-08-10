//
// Created by Tandra Ymir on 8/2/23.
//

#ifndef CONTAINERS_S21_ARRAY_H
#define CONTAINERS_S21_ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  constexpr array() : size_(N) {}

  constexpr explicit array(std::initializer_list<value_type> const &items) : array() {
    size_type i = 0;
    for (auto &&item : items) {
      array_[i++] = std::move(item);
    }
  }

  array(const array &a) : array() {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = a.array_[i];
    }
  }

  constexpr array(array &&a) noexcept : array(a) {}

  ~array() {}

  array operator=(array &&a) noexcept {

    for (size_type i = 0; i < size_; ++i) {
      array_[i] = std::move(a.array_[i]);
    }

    return *this;
  }

  constexpr reference at(size_type pos) {
    if (pos >= size_ || size_ == 0) {
      throw std::out_of_range("Index out range");
    }
    return *(array_ + pos);
  }

  constexpr reference operator[](size_type pos) { return *(array_ + pos); }

  constexpr const_reference front() { return *array_; }

  constexpr const_reference back() { return *(array_ + size_ - 1); }

  constexpr iterator data() { return array_; }

  constexpr iterator begin() { return array_; }

  constexpr iterator end() { return array_ + size_; }

  constexpr bool empty() { return size_ == 0; }

  constexpr size_type size() { return size_; }

  constexpr size_type max_size() { return size(); }

  constexpr void swap(array &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = value;
    }
  }

 private:
  size_type size_ = N;
  value_type array_[N];
};
}  // namespace s21

#endif  // CONTAINERS_S21_ARRAY_H
