// Copyright 2023 School21 @gruntmet Snezhana Valeeva
#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_H_
#include <functional>
#include <initializer_list>
#include <limits>
#include <utility>
namespace s21 {

template <class Key, class Compare = std::less<Key>>
class set;

template <class Key, class Compare = std::less<Key>>
struct AVLNode {
  Key value;
  int height;
  AVLNode* left;
  AVLNode* right;
  AVLNode* parent;

  explicit AVLNode(const Key& val)
      : value{val}, height{1}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  friend class set<Key, Compare>;
};

template <class Key, class Compare>
class set {
 public:
  template <class T>
  class ConstAVLIterator;
  template <class T>
  class AVLIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using const_iterator = ConstAVLIterator<value_type>;
  using iterator = AVLIterator<value_type>;
  using AVLNode = AVLNode<Key, Compare>;

  template <class T>
  class AVLIterator {
   public:
    using value_type = T;
    using reference = value_type&;
    using iterator = AVLIterator<value_type>;

    explicit AVLIterator<T>(AVLNode* node)
        : current_(node), root_for_iterator_(nullptr) {}
    AVLIterator<T>(AVLNode* node, AVLNode* root)
        : current_(node), root_for_iterator_(root) {}

    reference operator*() { return current_->value; }

    iterator& operator++() {
      if (current_->right != nullptr) {
        current_ = FindMin_(current_->right);
      } else {
        AVLNode* p = current_->parent;
        while (p != nullptr && current_ == p->right) {
          current_ = p;
          p = p->parent;
        }
        current_ = p;
      }
      return *this;
    }

    iterator& operator--() {
      if (current_ == nullptr) {
        current_ = FindMax_(root_for_iterator_);
      } else if (current_->left != nullptr) {
        current_ = FindMax_(current_->left);
      } else {
        AVLNode* p = current_->parent;
        while (p != nullptr && current_ == p->left) {
          current_ = p;
          p = p->parent;
        }
        current_ = p;
      }
      return *this;
    }

    bool operator==(const iterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) const {
      return current_ != other.current_;
    }

    AVLNode* current_;
    AVLNode* root_for_iterator_;

    AVLNode* FindMin_(AVLNode* node) {
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    AVLNode* FindMax_(AVLNode* node) {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }
  };

  template <class T>
  class ConstAVLIterator {
   public:
    using value_type = T;
    using const_reference = const value_type&;
    using const_iterator = ConstAVLIterator<value_type>;

    explicit ConstAVLIterator<T>(const AVLNode* node)
        : current_(node), root_for_iterator_(nullptr) {}
    ConstAVLIterator<T>(const AVLNode* node, const AVLNode* root)
        : current_(node), root_for_iterator_(root) {}

    const_reference operator*() const { return current_->value; }

    const_iterator& operator++() {
      if (current_->right != nullptr) {
        current_ = FindMin_(current_->right);
      } else {
        const AVLNode* p = current_->parent;
        while (p != nullptr && current_ == p->right) {
          current_ = p;
          p = p->parent;
        }
        current_ = p;
      }
      return *this;
    }

    const_iterator& operator--() {
      if (current_ == nullptr) {
        current_ = FindMax_(root_for_iterator_);
      } else if (current_->left != nullptr) {
        current_ = FindMax_(current_->left);
      } else {
        const AVLNode* p = current_->parent;
        while (p != nullptr && current_ == p->left) {
          current_ = p;
          p = p->parent;
        }
        current_ = p;
      }
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator& other) const {
      return current_ != other.current_;
    }

   private:
    const AVLNode* current_;
    const AVLNode* root_for_iterator_;

    const AVLNode* FindMin_(const AVLNode* node) const {
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    const AVLNode* FindMax_(const AVLNode* node) const {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }
  };

  set() : root_(nullptr), size_(0) {}

  set(std::initializer_list<value_type> const& items) : set() {
    for (const value_type& item : items) {
      insert(item);
    }
  }

  set(const set& s) : set() {
    for (const value_type& item : s) {
      insert(item);
    }
  }

  set(set&& s) noexcept : root_(s.root_), size_(s.size_) {
    s.root_ = nullptr;
    s.size_ = 0;
  }

  ~set() { RemoveTree_(root_); }

  set& operator=(set&& s) noexcept {
    if (this != &s) {
      clear();
      root_ = s.root_;
      size_ = s.size_;
      s.root_ = nullptr;
      s.size_ = 0;
    }
    return *this;
  }

  set& operator=(const set& s) {
    if (this != &s) {
      clear();
      for (const value_type& item : s) {
        insert(item);
      }
    }
    return *this;
  }

  iterator begin() noexcept { return iterator(FindMin_(root_)); }

  iterator end() noexcept { return iterator(nullptr, root_); }

  const_iterator begin() const noexcept {
    return const_iterator(FindMin_(root_));
  }

  const_iterator end() const noexcept { return const_iterator(nullptr, root_); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() - sizeof(set)) /
           sizeof(AVLNode);
  }

  void clear() {
    RemoveTree_(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const_reference value) {
    AVLNode* existing = FindNode_(value);
    if (existing != nullptr) {
      return std::make_pair(iterator(existing), false);
    }

    auto new_node = new AVLNode(value);
    root_ = InsertNode_(root_, new_node);
    ++size_;

    return std::make_pair(iterator(new_node), true);
  }

  void erase(iterator pos) {
    AVLNode* node = pos.current_;
    if (node == nullptr) {
      return;
    }
    root_ = RemoveNode_(root_, node->value);
    --size_;
  }

  void swap(set& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  void merge(set& other) {
    if (this != &other) {
      for (const value_type& item : other) {
        insert(item);
      }
      other.clear();
    }
  }

  iterator find(const Key& key) { return iterator(FindNode_(key)); }
  const_iterator find(const Key& key) const {
    return const_iterator(FindNode_(key));
  }

  bool contains(const Key& key) const {
    AVLNode* current = root_;

    while (current != nullptr) {
      if (Compare{}(key, current->value))
        current = current->left;
      else if (Compare{}(current->value, key))
        current = current->right;
      else
        return true;
    }

    return false;
  }

  iterator lower_bound(const Key& key) const {
    AVLNode* current = root_;
    AVLNode* lower = nullptr;

    while (current != nullptr) {
      if (Compare{}(current->value, key)) {
        current = current->right;
      } else {
        lower = current;
        current = current->left;
      }
    }

    return iterator(lower);
  }

  iterator upper_bound(const Key& key) const {
    AVLNode* current = root_;
    AVLNode* upper = nullptr;

    while (current != nullptr) {
      if (Compare{}(key, current->value)) {
        upper = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return iterator(upper);
  }

 private:
  AVLNode* root_;
  size_type size_;

  int GetHeight_(AVLNode* node) const {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  void UpdateHeight(AVLNode* node) {
    int left_height = GetHeight_(node->left);
    int right_height = GetHeight_(node->right);
    node->height =
        (left_height > right_height ? left_height : right_height) + 1;
  }

  int GetBalance_(AVLNode* node) const {
    if (node == nullptr) {
      return 0;
    }
    return GetHeight_(node->left) - GetHeight_(node->right);
  }

  AVLNode* RotateLeft_(AVLNode* node) {
    AVLNode* right_child = node->right;
    right_child->parent = node->parent;
    node->right = right_child->left;
    if (node->right != nullptr) {
      node->right->parent = node;
    }
    right_child->left = node;
    node->parent = right_child;
    UpdateHeight(node);
    UpdateHeight(right_child);
    return right_child;
  }

  AVLNode* RotateRight_(AVLNode* node) {
    AVLNode* left_child = node->left;
    left_child->parent = node->parent;
    node->left = left_child->right;
    if (node->left != nullptr) {
      node->left->parent = node;
    }
    left_child->right = node;
    node->parent = left_child;
    UpdateHeight(node);
    UpdateHeight(left_child);
    return left_child;
  }

  AVLNode* Balance_(AVLNode* node) {
    UpdateHeight(node);

    if (GetBalance_(node) == 2) {
      if (GetBalance_(node->left) < 0) node->left = RotateLeft_(node->left);
      return RotateRight_(node);
    }
    if (GetBalance_(node) == -2) {
      if (GetBalance_(node->right) > 0) node->right = RotateRight_(node->right);
      return RotateLeft_(node);
    }
    return node;
  }

  AVLNode* InsertNode_(AVLNode* node, AVLNode* new_node) {
    if (node == nullptr) {
      return new_node;
    }

    if (Compare{}(new_node->value, node->value)) {
      node->left = InsertNode_(node->left, new_node);
      node->left->parent = node;
    } else if (Compare{}(node->value, new_node->value)) {
      node->right = InsertNode_(node->right, new_node);
      node->right->parent = node;
    } else {
      return node;
    }

    return Balance_(node);
  }

  AVLNode* RemoveNode_(AVLNode* node, key_type key) {
    if (node == nullptr) return nullptr;

    if (Compare{}(key, node->value)) {
      node->left = RemoveNode_(node->left, key);
    } else if (Compare{}(node->value, key)) {
      node->right = RemoveNode_(node->right, key);
    } else {
      if (node->left == nullptr || node->right == nullptr) {
        AVLNode* temp = node->left ? node->left : node->right;
        if (temp == nullptr) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
        }
        delete temp;
      } else {
        AVLNode* temp = FindMin_(node->right);
        node->value = temp->value;
        node->right = RemoveNode_(node->right, temp->value);
      }
    }

    if (node == nullptr) return node;

    return Balance_(node);
  }

  AVLNode* FindMin_(AVLNode* node) const {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  void RemoveTree_(AVLNode* node) {
    if (node != nullptr) {
      RemoveTree_(node->left);
      RemoveTree_(node->right);
      delete node;
    }
  }

  AVLNode* FindNode_(const value_type& value) const {
    AVLNode* current = root_;

    while (current != nullptr) {
      if (Compare{}(value, current->value))
        current = current->left;
      else if (Compare{}(current->value, value))
        current = current->right;
      else
        return current;
    }

    return nullptr;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_H_
