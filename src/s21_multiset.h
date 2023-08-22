// Copyright 2023 School21 @gruntmet Snezhana Valeeva
#ifndef CPP2_S21_CONTAINERS_SRC_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_MULTISET_H_

#include <utility>

#include "s21_map.h"

namespace s21 {

template <typename Key>
class multiset;

template <typename T>
class MultisetIterator {
  friend class multiset<T>;

 public:
  MultisetIterator<T>& operator++() {
    if ((*iter).second > current_count_) {
      current_count_++;
    } else {
      ++iter;
      current_count_ = 1ul;
    }
    return *this;
  }

  MultisetIterator<T>& operator--() {
    if (current_count_ > 1) {
      current_count_--;
    } else {
      --iter;
      current_count_ = (*iter).second;
    }
    return *this;
  }

  T& operator*() { return (*iter).first; }

  bool operator==(const MultisetIterator<T>& other) const {
    return ((iter == other.iter) && (current_count_ == other.current_count_));
  }

  bool operator!=(const MultisetIterator<T>& other) const {
    return ((iter != other.iter) || (current_count_ != other.current_count_));
  }

 private:
  typename s21::map<T, size_t>::iterator iter;
  size_t current_count_;
  explicit MultisetIterator<T>(typename s21::map<T, size_t>::iterator it)
      : iter(it), current_count_(1ul) {}
  MultisetIterator<T>(typename s21::map<T, size_t>::iterator it, size_t count)
      : iter(it), current_count_(count) {}
};

template <typename T>
class MultisetConstIterator {
  friend class multiset<T>;

 public:
  MultisetConstIterator<T>& operator++() {
    if ((*iter).second > current_count_) {
      current_count_++;
    } else {
      ++iter;
      current_count_ = 1ul;
    }
    return *this;
  }

  MultisetConstIterator<T>& operator--() {
    if (current_count_ > 1) {
      current_count_--;
    } else {
      --iter;
      current_count_ = (*iter).second;
    }
    return *this;
  }

  T& operator*() { return (*iter).first; }

  bool operator==(const MultisetConstIterator<T>& other) const {
    return ((iter == other.iter) && (current_count_ == other.current_count_));
  }

  bool operator!=(const MultisetConstIterator<T>& other) const {
    return ((iter != other.iter) || (current_count_ != other.current_count_));
  }

 private:
  typename s21::map<T, size_t>::const_iterator iter;
  size_t current_count_;
  explicit MultisetConstIterator<T>(
      typename s21::map<T, size_t>::const_iterator it)
      : iter(it), current_count_(1ul) {}
  MultisetConstIterator<T>(typename s21::map<T, size_t>::const_iterator it,
                           size_t count)
      : iter(it), current_count_(count) {}
};

template <typename Key>
class multiset {
 public:
  using value_type = Key;
  using size_type = size_t;
  using iterator = MultisetIterator<Key>;
  using const_iterator = MultisetConstIterator<Key>;

  multiset() : counter_(), size_() {}

  multiset(std::initializer_list<value_type> const& items) : multiset() {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& ms) : counter_(ms.counter_), size_(ms.size_) {}

  multiset(multiset&& ms) noexcept
      : counter_(std::move(ms.counter_)), size_(std::move(ms.size_)) {
    ms.size_ = 0;
  }

  ~multiset() { counter_.clear(); }

  multiset& operator=(multiset&& ms) noexcept {
    if (this != &ms) {
      counter_ = std::move(ms.counter_);
      size_ = ms.size_;
      ms.size_ = 0;
    }
    return *this;
  }

  multiset& operator=(const multiset& ms) {
    if (this != &ms) {
      counter_ = ms.counter_;
      size_ = ms.size_;
    }
    return *this;
  }

  iterator begin() noexcept { return iterator(counter_.begin()); }
  iterator end() noexcept { return iterator(counter_.end(), 1lu); }
  const_iterator begin() const noexcept {
    return const_iterator(counter_.begin());
  }
  const_iterator end() const noexcept {
    return const_iterator(counter_.end(), 1lu);
  }

  bool empty() const { return counter_.empty(); }

  size_type size() const { return size_; }

  size_type max_size() const { return counter_.max_size(); }

  void clear() {
    counter_.clear();
    size_ = 0;
  }

  iterator insert(const value_type& value) {
    auto it = counter_.find(value);
    if (it != counter_.end()) {
      ++((*it).second);
    } else {
      it = (counter_.insert({value, 1})).first;
    }
    ++size_;
    return iterator(it, (*it).second);
  }

  void erase(iterator pos) {
    auto it = pos.iter;
    if (it != counter_.end()) {
      --size_;
      if ((*it).second > 1) {
        --(*(it)).second;
      } else {
        counter_.erase(it);
      }
    }
  }

  void swap(multiset& other) {
    counter_.swap(other.counter_);
    std::swap(size_, other.size_);
  }

  void merge(multiset& other) {
    for (const auto& item : other) {
      insert(item);
    }
    other.clear();
  }

  size_type count(const value_type& key) const {
    auto it = counter_.find(key);
    return (it != counter_.end()) ? (*it).second : 0;
  }

  iterator find(const value_type& key) { return iterator(counter_.find(key)); }

  const_iterator find(const value_type& key) const {
    return const_iterator(counter_.find(key));
  }

  bool contains(const value_type& key) const { return counter_.contains(key); }

  std::pair<iterator, iterator> equal_range(const value_type& key) {
    return {iterator(counter_.find(key)), iterator(++counter_.find(key))};
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const value_type& key) const {
    return {const_iterator(counter_.find(key)),
            const_iterator(++counter_.find(key))};
  }

  iterator lower_bound(const value_type& key) const {
    return iterator(counter_.lower_bound(key));
  }

  iterator upper_bound(const value_type& key) const {
    return iterator(counter_.upper_bound(key));
  }

 private:
  s21::map<Key, size_t> counter_;
  size_type size_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_MULTISET_H_
