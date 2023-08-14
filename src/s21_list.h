//
// Created by Tandra Ymir on 7/27/23.
//

#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;

 private:
  struct Node;

 public:
  class ListConstIterator {
    friend class list<T>;

   public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using const_pointer = const T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ListConstIterator() : node_() {}

    explicit ListConstIterator(Node *node) : node_(node) {}
    ListConstIterator(ListIterator iter) { node_ = iter.node_; }

    const_reference operator*() const { return node_->value_; }

    const_pointer operator->() const { return &node_->value_; }

    ListConstIterator &operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator temp(*this);
      node_ = node_->next_;
      return temp;
    }

    ListConstIterator &operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator temp(*this);
      node_ = node_->prev_;
      return temp;
    }

    bool operator==(const ListConstIterator &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListConstIterator &other) const {
      return node_ != other.node_;
    }

   private:
    Node *node_;
  };

  class ListIterator {
    friend list;

   public:
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ListIterator() : node_() {}

    explicit ListIterator(Node *node) : node_(node) {}

    ListIterator(ListConstIterator iter) { node_ = iter.node_; }

    reference operator*() const { return node_->value_; }

    pointer operator->() const { return &node_->value_; }

    ListIterator &operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp(*this);
      node_ = node_->next_;
      return temp;
    }

    ListIterator &operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator temp(*this);
      node_ = node_->prev_;
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListIterator &other) const {
      return node_ != other.node_;
    }

   private:
    Node *node_;
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;

  list() : size_(0) {
    fantom_node_ = new Node(T());
    fantom_node_->prev_ = fantom_node_;
    fantom_node_->next_ = fantom_node_;
  }

  explicit list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(T());
    }
  }

  explicit list(std::initializer_list<value_type> const &items) noexcept
      : list() {
    for (const_reference value_ : items) {
      push_back(value_);
    }
  }

  list(const list &other) : list() {
    for (const_reference value_ : other) {
      push_back(value_);
    }
  }

  list(list &&other) noexcept {
    size_ = std::move(other.size_);
    fantom_node_ = std::move(other.fantom_node_);
    other.size_ = 0;
    other.fantom_node_ = nullptr;
  }

  ~list() {
    while (!empty()) {
      if (fantom_node_->prev_ != fantom_node_) {
        Node *prev_tail = fantom_node_->prev_;
        Node *new_tail = prev_tail->prev_;
        new_tail->next_ = fantom_node_;
        fantom_node_->prev_ = new_tail;
        delete prev_tail;
        --size_;
      }
    }
    delete fantom_node_;
  }

  list &operator=(const list &other) {
    if (this == &other) {
      return *this;
    }
    clear();
    for (const T &value_ : other) {
      push_back(value_);
    }
    return *this;
  }

  list &operator=(list &&other) noexcept {
    while (!empty()) {
      pop_back();
    }
    delete fantom_node_;
    fantom_node_ = std::move(other.fantom_node_);
    size_ = other.size_;
    other.size_ = 0;
    other.fantom_node_ = nullptr;
    return *this;
  }

  const_reference front() const { return fantom_node_->next_->value_; }

  const_reference back() const { return fantom_node_->prev_->value_; }

  iterator begin() { return iterator(fantom_node_->next_); }

  iterator end() { return iterator(fantom_node_); }

  const_iterator begin() const { return const_iterator(fantom_node_->next_); }

  const_iterator end() const { return const_iterator(fantom_node_); }

  bool empty() const noexcept { return size_ == 0; }

  size_t size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
  }

  void clear() noexcept {
    while (size_ > 0) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value_) {
    Node *next_node = pos.node_;
    Node *insert_node = new Node(value_);
    next_node->prev_->InsertNode(insert_node, next_node);
    ++size_;
    return iterator(insert_node);
  }

  void erase(iterator pos) {
    Node *erase_node = pos.node_;
    if (pos.node_ == fantom_node_) {
      return;
    }
    erase_node->prev_->next_ = erase_node->next_;
    erase_node->next_->prev_ = erase_node->prev_;
    delete pos.node_;
    --size_;
  }

  void push_back(const_reference value_) {
    Node *new_node = new Node(value_);
    fantom_node_->prev_->InsertNode(new_node, fantom_node_);
    ++size_;
  }

  void pop_back() {
    Node *prev_tail = fantom_node_->prev_;
    Node *new_tail = prev_tail->prev_;
    new_tail->next_ = fantom_node_;
    fantom_node_->prev_ = new_tail;
    delete prev_tail;
    --size_;
  }

  void push_front(const_reference value_) {
    Node *new_node = new Node(value_);
    fantom_node_->InsertNode(new_node, fantom_node_->next_);
    ++size_;
  }

  void pop_front() {
    Node *prev_head = fantom_node_->next_;
    Node *new_head = prev_head->next_;
    new_head->prev_ = fantom_node_;
    fantom_node_->next_ = new_head;
    delete prev_head;
    --size_;
  }

  void swap(list &other) {
    std::swap(fantom_node_, other.fantom_node_);
    std::swap(size_, other.size_);
  }

  void merge(list &other) {
    if (this == &other) {
      return;
    }
    if (other.empty()) {
      return;
    }

    Node *this_node = fantom_node_->next_;
    Node *other_node = other.fantom_node_->next_;

    while (this_node != fantom_node_ && other_node != other.fantom_node_) {
      if (other_node->value_ <= this_node->value_) {
        Node *cur_other_node = other_node;
        other_node = other_node->next_;
        this_node->prev_->InsertNode(cur_other_node, this_node);

      } else {
        this_node = this_node->next_;
      }
    }

    if (other_node != other.fantom_node_) {
      fantom_node_->prev_->InsertNode(other_node, other_node->next_);
      other.fantom_node_->prev_->prev_->InsertNode(other.fantom_node_->prev_,
                                                   fantom_node_);
    }

    size_ += other.size_;
    other.size_ = 0;
  }

  void splice(const_iterator pos, list &other) {
    if (this == &other) {
      return;
    }

    if (other.empty()) {
      return;
    }
    pos.node_->prev_->InsertNode(other.fantom_node_->next_,
                                 other.fantom_node_->next_->next_);
    other.fantom_node_->prev_->prev_->InsertNode(other.fantom_node_->prev_,
                                                 pos.node_);

    size_ += other.size_;
    other.size_ = 0;
  }

  void reverse() noexcept {
    if (size() < 2) {
      return;
    }
    while (fantom_node_->next_ != fantom_node_) {
      fantom_node_->next_->next_ = fantom_node_->next_->prev_;
      fantom_node_->next_->prev_ = fantom_node_->next_->next_;
      fantom_node_->next_ = fantom_node_->next_->next_;
    }
    fantom_node_->next_ = fantom_node_->prev_;
    fantom_node_->prev_ = fantom_node_->next_;
  }

  void unique() {
    if (size_ <= 1) {
      return;
    }
    while (fantom_node_->next_->next_ != fantom_node_) {
      if (fantom_node_->next_->value_ == fantom_node_->next_->next_->value_) {
        erase(iterator(fantom_node_->next_->next_));
      } else {
        fantom_node_->next_ = fantom_node_->next_->next_;
      }
    }
  }

  void sort(std::less<value_type> cmp = std::less<value_type>{}) {
    MergeSort(begin(), end(), cmp);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    Node *prev_node = pos.node_->prev_;
    Node *next_node = pos.node_;
    list<value_type> init_list{std::forward<Args>(args)...};
    prev_node->next_ = init_list.fantom_node_->next_;
    next_node->prev_ = init_list.fantom_node_->prev_;
    init_list.fantom_node_->next_->prev_ = prev_node;
    init_list.fantom_node_->prev_->next_ = next_node;

    size_ += init_list.size();

    return iterator(prev_node->next_);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    list init_list{std::forward<Args>(args)...};
    splice(end(), init_list);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list init_list{std::forward<Args>(args)...};
    splice(begin(), init_list);
  }

 private:
  struct Node {
    Node *prev_;
    Node *next_;
    value_type value_;

    explicit Node(const T &data)
        : prev_(nullptr), next_(nullptr), value_(data) {}

    void InsertNode(Node *insert_node, Node *next_node) {
      next_node->prev_ = insert_node;
      insert_node->next_ = next_node;
      this->next_ = insert_node;
      insert_node->prev_ = this;
    }
  };

  void MergeSort(iterator begin, iterator end, std::less<value_type> cmp) {
    const auto num_elem = std::distance(begin, end);
    if (num_elem > 1) {
      const auto middle = std::next(begin, num_elem / 2);
      MergeSort(begin, middle, cmp);
      MergeSort(middle, end, cmp);
      std::inplace_merge(begin, middle, end, cmp);
    }
  }
  size_type size_;
  Node *fantom_node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_