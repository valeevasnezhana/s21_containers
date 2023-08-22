// Copyright 2023 School21 @tandraym
#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

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

  constexpr explicit array(std::initializer_list<value_type> const &items)
      : array() {
    size_type i = 0;
    for (auto const &item : items) {
      array_[i++] = std::move(item);
    }
  }

  constexpr array(const array &a) : array() {
    std::copy(a.array_, a.array_ + size_, array_);
  }

  constexpr array(array &&a) noexcept : array() {
    std::move(a.array_, a.array_ + size_, array_);
  }

  ~array() {}

  constexpr array operator=(array &&a) noexcept {
    std::move(a.array_, a.array_ + size_, array_);
    return *this;
  }

  constexpr array operator=(array &a) {
    std::copy(a.array_, a.array_ + size_, array_);
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

  constexpr void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = value;
    }
  }

 private:
  size_type size_ = N;
  value_type array_[N];
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
