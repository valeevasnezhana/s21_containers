// Copyright 2023 School21 @gruntmet Snezhana Valeeva
#ifndef CPP2_S21_CONTAINERS_SRC_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_S21_MAP_H_

#include <functional>
#include <initializer_list>
#include <limits>
#include <utility>

#include "s21_set.h"
namespace s21 {

template <class Key, class T, class Compare = std::less<Key> >
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  template <class First, class Second>
  class MyPair_ {
   public:
    MyPair_<First, Second>(First first, Second second)
        : first{first}, second{second} {}
    MyPair_<First, Second>(const MyPair_<First, Second> &other)
        : first(other.first), second(other.second) {}

    First first;
    Second second;
  };

  struct InMapCompare_ {
    constexpr bool operator()(const MyPair_<key_type, mapped_type> &lhs,
                              const MyPair_<key_type, mapped_type> &rhs) const {
      return Compare{}(lhs.first, rhs.first);
    }
  };

  using SetValueType_ = MyPair_<key_type, mapped_type>;
  using SetTemplate_ = s21::set<SetValueType_, InMapCompare_>;

 public:
  using iterator = typename SetTemplate_::iterator;
  using const_iterator = typename SetTemplate_::const_iterator;

  map() : data_{} { ; }

  map(std::initializer_list<value_type> const &items) {
    for (const value_type &item : items) {
      insert(item.first, item.second);
    }
  }

  map(const map &other) : data_(other.data_) { ; }
  map(map &&other) noexcept : data_(std::move(other.data_)) { ; }

  map &operator=(map &&other) noexcept {
    data_ = std::move(other.data_);
    return *this;
  }

  map &operator=(const map &other) {
    data_ = other.data_;
    return *this;
  }

  ~map() { data_.clear(); }

  void swap(map &other) { std::swap(*this, other); }
  void merge(map &other) { data_.merge(other.data_); }

  bool empty() const { return data_.empty(); }
  size_type size() const { return data_.size(); }
  size_type max_size() const { return data_.max_size(); }

  iterator begin() noexcept { return data_.begin(); }
  iterator end() noexcept { return data_.end(); }
  const_iterator begin() const noexcept { return data_.begin(); }
  const_iterator end() const noexcept { return data_.end(); }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &mapped) {
    return data_.insert(SetValueType_(key, mapped));
  }

  std::pair<iterator, bool> insert(const_reference value) {
    return data_.insert(SetValueType_(value.first, value.second));
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    bool status = contains(key);
    if (status) {
      at(key) = obj;
    } else {
      insert(key, obj);
    }
    auto it = (data_.insert(SetValueType_(key, obj))).first;
    return std::make_pair(it, !status);
  }

  void erase(iterator pos) { data_.erase(pos); }

  mapped_type &operator[](const key_type &key) {
    auto it = data_.find(SetValueType_(key, mapped_type()));

    if (it == data_.end()) {
      it = (data_.insert(SetValueType_(key, mapped_type()))).first;
    }
    return (*it).second;
  }

  const mapped_type &at(const Key &key) const {
    auto it = data_.find(SetValueType_(key, mapped_type()));
    if (it == data_.end()) throw std::out_of_range("Incorrect index");
    return (*it).second;
  }

  mapped_type &at(const Key &key) {
    auto it = data_.find(SetValueType_(key, mapped_type()));
    if (it == data_.end()) throw std::out_of_range("Incorrect index");
    return (*it).second;
  }

  bool contains(const key_type &key) const {
    return data_.contains(SetValueType_(key, mapped_type()));
  }

  iterator find(const Key &key) {
    return data_.find(SetValueType_(key, mapped_type()));
  }

  const_iterator find(const Key &key) const {
    return data_.find(SetValueType_(key, mapped_type()));
  }

  iterator upper_bound(const Key &key) const {
    return data_.upper_bound(SetValueType_(key, mapped_type()));
  }

  iterator lower_bound(const Key &key) const {
    return data_.lower_bound(SetValueType_(key, mapped_type()));
  }

  void clear() { data_.clear(); }

 private:
  SetTemplate_ data_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_MAP_H_
