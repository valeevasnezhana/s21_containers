#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_H_
#include <initializer_list>
#include <utility>
namespace s21 {

template <class Key>
class set {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

 private:
  struct AVLNode {
    value_type value;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

    explicit AVLNode(const value_type& val)
        : value(val),
          height(1),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

 public:
  class iterator {
   public:
    explicit iterator(AVLNode* node) : current(node) {}

    reference operator*() const { return current->value; }

    iterator& operator++() {
      if (current->right != nullptr) {
        current = find_min(current->right);
      } else {
        AVLNode* p = current->parent;
        while (p != nullptr && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    iterator& operator--() {
      if (current->left != nullptr) {
        current = find_max(current->left);
      } else {
        AVLNode* p = current->parent;
        while (p != nullptr && current == p->left) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return (current != other.current);
    }

    AVLNode* current;

    AVLNode* find_min(AVLNode* node) {
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    AVLNode* find_max(AVLNode* node) {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }
  };

  class const_iterator {
   public:
    explicit const_iterator(const AVLNode* node) : current(node) {}

    const_reference operator*() const {
      if (current) {
        return current->value;
      }
      return value_type();
    }

    const_iterator& operator++() {
      if (current->right != nullptr) {
        current = find_min(current->right);
      } else {
        const AVLNode* p = current->parent;
        while (p != nullptr && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    const_iterator& operator--() {
      if (current->left != nullptr) {
        current = find_max(current->left);
      } else {
        const AVLNode* p = current->parent;
        while (p != nullptr && current == p->left) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const const_iterator& other) const {
      return current != other.current;
    }

   private:
    const AVLNode* current;

    const AVLNode* find_min(const AVLNode* node) {
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    const AVLNode* find_max(const AVLNode* node) {
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }
  };

  set() : root_(nullptr), size_(0){};

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

  ~set() { clear(root_); }

  set& operator=(set&& s) noexcept {
    if (this != &s) {
      clear(root_);
      root_ = s.root_;
      size_ = s.size_;
      s.root_ = nullptr;
      s.size_ = 0;
    }
    return *this;
  }

  iterator begin() { return iterator(find_min(root_)); }

  iterator end() { return iterator(nullptr); }

  const_iterator begin() const { return const_iterator(find_min(root_)); }

  const_iterator end() const { return const_iterator(nullptr); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const { return size_type(-1); }

  void clear() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    AVLNode* existing = find_node(root_, value);
    if (existing != nullptr) {
      return std::make_pair(iterator(existing), false);
    }

    auto new_node = new AVLNode(value);
    root_ = insert_node(root_, new_node);
    size_++;

    return std::make_pair(iterator(new_node), true);
  }

  void erase(iterator pos) {
    AVLNode* node = pos.current;
    if (node == nullptr) {
      return;
    }
    root_ = erase_node(root_, node);
    size_--;
  }

  iterator find(const Key& key) { return iterator(find_node(root_, key)); }

  bool contains(const Key& key) {
    AVLNode* current = root_;

    while (current != nullptr) {
      if (key < current->value)
        current = current->left;
      else if (key > current->value)
        current = current->right;
      else
        return true;
    }

    return false;
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

 private:
  AVLNode* root_;
  size_type size_;

  int get_height(AVLNode* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  void update_height(AVLNode* node) {
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    node->height =
        (left_height > right_height ? left_height : right_height) + 1;
  }

  int get_balance(AVLNode* node) {
    if (node == nullptr) {
      return 0;
    }
    return get_height(node->left) - get_height(node->right);
  }

  AVLNode* rotate_left(AVLNode* node) {
    AVLNode* right_child = node->right;
    right_child->parent = node->parent;
    node->right = right_child->left;
    if (node->right != nullptr) {
      node->right->parent = node;
    }
    right_child->left = node;
    node->parent = right_child;
    update_height(node);
    update_height(right_child);
    return right_child;
  }

  AVLNode* rotate_right(AVLNode* node) {
    AVLNode* left_child = node->left;
    left_child->parent = node->parent;
    node->left = left_child->right;
    if (node->left != nullptr) {
      node->left->parent = node;
    }
    left_child->right = node;
    node->parent = left_child;
    update_height(node);
    update_height(left_child);
    return left_child;
  }

  AVLNode* insert_node(AVLNode* node, AVLNode* new_node) {
    if (node == nullptr) {
      return new_node;
    }

    if (new_node->value < node->value) {
      node->left = insert_node(node->left, new_node);
      node->left->parent = node;
    } else if (new_node->value > node->value) {
      node->right = insert_node(node->right, new_node);
      node->right->parent = node;
    } else {
      return node;
    }

    update_height(node);

    int balance = get_balance(node);

    if (balance > 1 && new_node->value < node->left->value) {
      return rotate_right(node);
    }

    if (balance < -1 && new_node->value > node->right->value) {
      return rotate_left(node);
    }

    if (balance > 1 && new_node->value > node->left->value) {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }

    if (balance < -1 && new_node->value < node->right->value) {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    }

    return node;
  }

  AVLNode* erase_node(AVLNode* node, AVLNode* deleted) {
    if (node == nullptr) {
      return nullptr;
    }

    if (deleted->value < node->value) {
      node->left = erase_node(node->left, deleted);
    } else if (deleted->value > node->value) {
      node->right = erase_node(node->right, deleted);
    } else {
      if (node->left == nullptr || node->right == nullptr) {
        AVLNode* temp = (node->left != nullptr) ? node->left : node->right;
        if (temp == nullptr) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
        }
        delete temp;
      } else {
        AVLNode* successor = find_min(node->right);
        node->value = successor->value;
        node->right = erase_node(node->right, successor);
      }
    }

    if (node == nullptr) {
      return nullptr;
    }

    update_height(node);

    int balance = get_balance(node);

    if (balance > 1 && get_balance(node->left) >= 0) {
      return rotate_right(node);
    }

    if (balance > 1 && get_balance(node->left) < 0) {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }

    if (balance < -1 && get_balance(node->right) <= 0) {
      return rotate_left(node);
    }

    if (balance < -1 && get_balance(node->right) > 0) {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    }

    return node;
  }

  AVLNode* find_min(AVLNode* node) const {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  void clear(AVLNode* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  AVLNode* find_node(AVLNode* node, const value_type& value) {
    if (node == nullptr || value == node->value) {
      return node;
    }
    if (value < node->value) {
      return find_node(node->left, value);
    }
    return find_node(node->right, value);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_H_
