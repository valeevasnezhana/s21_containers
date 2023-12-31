// Copyright 2023 School21 @tandraym
#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <limits>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using pointer = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  vector() : size_(0), capacity_(0), array_(nullptr) {}

  explicit vector(size_type n)
      : size_(n), capacity_(n), array_(new value_type[n]) {
    std::fill(array_, array_ + n, T());
  }

  explicit vector(std::initializer_list<value_type> const &items)
      : size_(items.size()),
        capacity_(items.size()),
        array_(new value_type[items.size()]) {
    std::copy(items.begin(), items.end(), array_);
  }

  vector(const vector &other)
      : size_(other.size_),
        capacity_(other.capacity_),
        array_(new value_type[capacity_]) {
    std::copy(other.array_, other.array_ + other.size_, array_);
  }

  vector(vector &&other) noexcept
      : size_(other.size_), capacity_(other.capacity_), array_(other.array_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
  }

  vector &operator=(const vector &other) {
    if (this == &other) {
      return *this;
    }
    delete[] array_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = new value_type[capacity_];

    std::copy(other.array_, other.array_ + other.size_, array_);

    return *this;
  }

  vector &operator=(vector &&other) noexcept {
    delete[] array_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = other.array_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
    return *this;
  }

  ~vector() { delete[] array_; }

  reference at(size_type pos) {
    if (pos >= size_ || size_ == 0) {
      throw std::out_of_range("Out of bound exeption");
    }
    return *(array_ + pos);
  }

  reference operator[](size_type pos) { return *(array_ + pos); }

  const_reference front() const { return *array_; }

  const_reference back() const { return *(array_ + size_ - 1); }

  iterator data() noexcept { return array_; }
  const_iterator data() const noexcept { return array_; }

  iterator begin() noexcept { return array_; }

  const_iterator begin() const noexcept { return array_; }

  iterator end() noexcept { return array_ + size_; }

  const_iterator end() const noexcept { return array_ + size_; }

  bool empty() const noexcept {
    if (size_ == 0) {
      return true;
    }
    return false;
  }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    T *new_array = new value_type[size];
    std::move(array_, array_ + size_, new_array);
    delete[] array_;
    array_ = new_array;
    capacity_ = size;
  }

  void push_back(const_reference value) {
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    array_[size_] = value;
    ++size_;
  }

  void pop_back() { --size_; }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      T *new_array = new value_type[size_];
      std::move(array_, array_ + size_, new_array);
      delete[] array_;
      array_ = new_array;
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - array_;
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    for (size_type i = size_; i > index; --i) {
      array_[i] = std::move(array_[i - 1]);
    }
    array_[index] = value;
    ++size_;
    return pos;
  }

  void erase(iterator pos) {
    size_type del = pos - begin();
    for (; del < size_ - 1; ++del) {
      array_[del] = std::move(array_[del + 1]);
    }
    --size_;
  }

  void swap(vector &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type num_elems = sizeof...(Args);
    size_type insert_pos = pos - array_;
    if (size_ + num_elems >= capacity_) {
      reserve(size_ + num_elems);
    }
    for (size_type i = size_ - 1; i >= insert_pos; --i) {
      array_[i + num_elems] = std::move(array_[i]);
    }
    ((array_[insert_pos++] = std::forward<Args>(args)), ...);
    size_ += num_elems;

    return array_ + insert_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

 private:
  size_type size_;
  size_type capacity_;
  pointer array_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_