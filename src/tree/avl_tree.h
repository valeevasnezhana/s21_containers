// Copyright 2023 School21 @gruntmet Snezhana Valeeva
#ifndef CPP2_S21_CONTAINERS_SRC_TREE_S21_AVL_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_TREE_S21_AVL_TREE_H_

#include <algorithm>
#include <initializer_list>
#include <utility>
namespace s21 {
template <typename K, typename V>
struct Node {
  Node();
  Node(K o_value, int o_height);

  Node* next_node();
  Node* previous_node();

  K value;
  int height;
  Node *parent = nullptr, *left = nullptr, *right = nullptr;
};

template <typename K, typename V>
class AVLTree {
 public:
  class Iterator;
  class ConstIterator;

  using node_type = Node<K, V>;
  using reference = V&;
  using const_reference = const V&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  AVLTree() noexcept;
  explicit AVLTree(std::initializer_list<K> const& init);
  explicit AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other) noexcept;
  ~AVLTree();

  node_type* insert(const K& key);
  void merge(const AVLTree& other);
  void erase(node_type*);
  node_type* find(const K& key);
  node_type* lower_bound(const K& key);
  void clear();

  bool empty() const;
  size_t get_size() const;
  size_t max_size() const;

  AVLTree& operator=(const AVLTree& other);
  AVLTree& operator=(AVLTree&& other);

  node_type* begin();
  node_type* end();

  class Iterator {
   public:
    Iterator();
    explicit Iterator(node_type* node);
    explicit Iterator(const iterator& other);
    explicit Iterator(iterator&& other);

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    iterator& operator=(const iterator& s);
    iterator& operator=(iterator&& s);
    bool operator!=(const iterator& it);
    bool operator==(const iterator& it);
    K& operator*();

   protected:
    node_type* iterator_node_;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator{} {};
    explicit ConstIterator(node_type* node) : Iterator{node} {};
    explicit ConstIterator(const const_iterator& other) : Iterator{other} {};
    explicit ConstIterator(const iterator& other) : Iterator{other} {};
    explicit ConstIterator(const_iterator&& other)
        : Iterator{std::move(other)} {};
    const K& operator*();
  };

 private:
  size_t size_;
  node_type* head_;

  void delete_nodes(node_type* node);
  void swap_node(node_type* one, node_type* two);

  AVLTree& copy_tree(node_type* node, const node_type* other_node);
  AVLTree& swap_tree(AVLTree<K, V>&& other_tree);

  node_type* inner_insert(node_type* node, const K& key);

  void balance(node_type* node, int diff);
  int get_balance(const node_type* node) const;
  void balance_after_erase(node_type* node);

  int get_height(const node_type* node) const;
  void update_height(node_type* node);

  void left_rotate(node_type* node);
  void right_rotate(node_type* node);

  node_type* find_extremum(node_type* node, int balance);

  void create_end();
};
}  // namespace s21

namespace s21 {
template <typename T, typename V>
typename AVLTree<T, V>::AVLTree()
    : root(nullptr), nil(nullptr), inserted(false) {}
template <typename T, typename V>
AVLTree<T, V>::AVLTree(const AVLTree& other)
    : root(CopyTree(other.GetRoot())) {}
template <typename T, typename V>
AVLTree<T, V>& AVLTree<T, V>::operator=(AVLTree&& other) noexcept {
  if (this != &other) {
    Clear(root);
    root = exchange(other.root, nullptr);
  }
  return *this;
}
template <typename T, typename V>
int AVLTree<T, V>::Height(Node<T, V>* node) {
  if (!node) return 0;
  return node->height;
}
template <typename T, typename V>
int AVLTree<T, V>::BalanceFactor(Node<T, V>* node) {
  if (!node) return 0;
  return (Height(node->left) - Height(node->right));
}
template <typename T, typename V>
void AVLTree<T, V>::UpdateHeight(Node<T, V>* node) {
  int hl = Height(node->left);
  int hr = Height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RotateRight(Node<T, V>* node) {
  Node<T, V>* newRoot = node->left;
  node->left = newRoot->right;
  if (newRoot->right) {
    newRoot->right->parent = node;
  }
  newRoot->right = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;
  UpdateHeight(newRoot);
  UpdateHeight(node);
  return newRoot;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RotateLeft(Node<T, V>* node) {
  Node<T, V>* newRoot = node->right;
  node->right = newRoot->left;
  if (newRoot->left) {
    newRoot->left->parent = node;
  }
  newRoot->left = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;
  UpdateHeight(newRoot);
  UpdateHeight(node);
  return newRoot;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Balance(Node<T, V>* node) {
  UpdateHeight(node);
  if (BalanceFactor(node) == 2) {
    if (BalanceFactor(node->right) < -1) {
      node->left = RotateLeft(node->left);
      UpdateSize(node->left);
    }
    node = RotateRight(node);
    UpdateSize(node);
  }
  if (BalanceFactor(node) == -2) {
    if (BalanceFactor(node->left) > 1) {
      node->right = RotateRight(node->right);
      UpdateSize(node->right);
    }
    node = RotateLeft(node);
    UpdateSize(node);
  }
  UpdateSize(node);
  return node;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Insert(Node<T, V>* node, T key, Node<T, V>* parent) {
  this->inserted = false;
  if (!node) {
    node = new Node<T, V>(key);
    node->parent = parent;
    this->inserted = true;
    return Balance(node);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key, node);
  } else if (key > node->key) {
    node->right = Insert(node->right, key, node);
  } else {
    this->inserted = false;
  }
  return Balance(node);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::FindMin(Node<T, V>* node) {
  if (!node->left) return node;
  return FindMin(node->left);
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RemoveMin(Node<T, V>* node) {
  if (!node->left) return node->right;
  node->left = RemoveMin(node->left);
  return Balance(node);
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Remove(Node<T, V>* node, T key) {
  if (!node) return nullptr;
  if (key < node->key) {
    node->left = Remove(node->left, key);
  } else if (key > node->key) {
    node->right = Remove(node->right, key);
  } else {
    Node<T, V>* left = node->left;
    Node<T, V>* right = node->right;
    if (!right) return left;
    if (!left) return right;
    Node<T, V>* min = FindMin(right);
    min->right = RemoveMin(right);
    min->left = left;
    min->size_--;
    min->parent = node->parent;
    UpdateHeight(min);
    delete node;
    return Balance(min);
  }
  node->size_--;
  UpdateHeight(node);
  return Balance(node);
}
template <typename T, typename V>
AVLTree<T, V>::~AVLTree() {
  Clear(root);
}
template <typename T, typename V>
void AVLTree<T, V>::Clear(Node<T, V>* node) {
  if (node != nullptr) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
  root = nullptr;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Search(Node<T, V>* node, T key) {
  if (!node || node->key == key) {
    return node;
  }
  if (key < node->key) {
    return Search(node->left, key);
  } else {
    return Search(node->right, key);
  }
}
template <typename T, typename V>
void AVLTree<T, V>::SetRoot(Node<T, V>* root) {
  this->root = root;
  if (this->root != nullptr) {
    this->root->parent = nullptr;
  }
}
template <typename T, typename V>
void AVLTree<T, V>::UpdateSize(Node<T, V>* node) {
  if (node) {
    node->size_ = 1 + Size(node->left) + Size(node->right);
    UpdateSize(node->left);
    UpdateSize(node->right);
  }
}
template <typename T, typename V>
int AVLTree<T, V>::Size(Node<T, V>* node) {
  if (node) {
    return node->size_;
  }
  return 0;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Insert(T key) {
  root = Insert(root, key, nullptr);
  return root;
}
template <typename T, typename V>
void AVLTree<T, V>::Remove(T key) {
  root = Remove(root, key);
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Search(T key) {
  return Search(root, key);
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::GetRoot() const {
  return this->root;
}
template <typename T, typename V>
void AVLTree<T, V>::Swap(AVLTree<T, V>& other) {
  std::swap(root, other.root);
}
template <typename T, typename V>
bool AVLTree<T, V>::GetInserted() {
  return inserted;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::CopyTree(Node<T, V>* node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node<T, V>* new_node = new Node<T, V>(node->key);
  new_node->size_ = node->size_;
  new_node->left = CopyTree(node->left);
  new_node->right = CopyTree(node->right);
  new_node->parent = node->parent;
  return new_node;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::MaximumKey(Node<T, V>* node) {
  if (node != nullptr) {
    while (node->right != nullptr) {
      return this->MaximumKey(node->right);
    }
    return node;
  }
  return nullptr;
}
template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::GetNil() {
  return nil;
}
}  // namespace s21

namespace s21 {

template <typename T, typename V>
class Iterator {
 public:
  using key_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;

  explicit Iterator(Node<T, V>* node = nullptr) : node_(node) {}
  Iterator(Node<T, V>* nil, Node<T, V>* root) : node_(nil), root_(root) {}
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  ~Iterator() = default;
  Iterator operator+(const size_t value) {
    Iterator tmp = *this;
    for (size_t i = 0; i < value; i++) {
      ++tmp;
    }
    return tmp;
  }
  Iterator& operator++() {
    if (node_ != nullptr) {
      if (node_->right != nullptr) {
        node_ = node_->right;
        while (node_->left != nullptr) {
          node_ = node_->left;
        }
      } else {
        Node<T, V>* parent = node_->parent;
        while (parent != nullptr && node_ == parent->right) {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }
  Iterator& operator--() {
    if (Size(root_) > 0) {
      if (node_ != nullptr) {
        return OperatorHelper();
      }
      node_ = MaximumKey(root_);
      return *this;
    }
    return OperatorHelper();
  }

  Iterator operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const Iterator& other) const { return node_ == other.node_; }
  bool operator!=(const Iterator& other) const { return node_ != other.node_; }

  reference operator*() const {
    if (node_ == nullptr) {
      static T default_value = T{};
      return default_value;
    }
    return node_->key;
  }
  pointer operator->() const { return &(node_->key); }
  int Size(Node<T, V>* node) {
    if (node) {
      return node->size_;
    }
    return 0;
  }
  Node<T, V>* MaximumKey(Node<T, V>* node) {
    if (node != nullptr) {
      if (node->right != nullptr) {
        return this->MaximumKey(node->right);
      }
      return node;
    }
    return nullptr;
  }
  Iterator& OperatorHelper() {
    if (node_ != nullptr) {
      if (node_->left != nullptr) {
        node_ = node_->left;
        while (node_->right != nullptr) {
          node_ = node_->right;
        }
      } else {
        Node<T, V>* parent = node_->parent;
        while (parent != nullptr && node_ == parent->left) {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }
    return *this;
  }

 protected:
  Node<T, V>* node_;
  Node<T, V>* root_;
};

template <typename T, typename V>
class ConstIterator : public Iterator<const T, const V> {
 public:
  using Iterator<const T, const V>::Iterator;

  using typename Iterator<const T, const V>::key_type;
  using typename Iterator<const T, const V>::reference;
  using typename Iterator<const T, const V>::const_reference;
  using typename Iterator<const T, const V>::pointer;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_TREE_S21_AVL_TREE_H_
