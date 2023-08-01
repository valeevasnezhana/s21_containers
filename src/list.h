//
// Created by Tandra Ymir on 7/27/23.
//

#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include <cstddef>
#include <iostream>

template<typename T>
class list {
private:
    struct BaseNode {
        BaseNode *prev;
        BaseNode *next;

        BaseNode() : prev(nullptr), next(nullptr) {}
    };

    struct Node : public BaseNode {
        T value;
        explicit Node(const T &data) : value(data) {}
    };

public:
    class ListConstIterator {
        friend list;
    public:
        using value_type = T;
        using reference = const T &;
        using pointer = const T *;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        ListConstIterator() : node_(nullptr) {}

        explicit ListConstIterator(const BaseNode *node) : node_(node) {}

        reference operator*() const {
            return static_cast<const Node *>(node_)->value;
        }

        pointer operator->() const {
            return &(static_cast<const Node *>(node_)->value);
        }

        ListConstIterator &operator++() {
            node_ = node_->next;
            return *this;
        }

        ListConstIterator operator++(int) {
            ListConstIterator temp = *this;
            node_ = node_->next;
            return temp;
        }

        ListConstIterator &operator--() {
            node_ = node_->prev;
            return *this;
        }

        ListConstIterator operator--(int) {
            ListConstIterator temp = *this;
            node_ = node_->prev;
            return temp;
        }

        bool operator==(const ListConstIterator &other) const {
            return node_ == other.node_;
        }

        bool operator!=(const ListConstIterator &other) const {
            return node_ != other.node_;
        }

    private:
        const BaseNode *node_;
    };

    // Define iterator by inheriting from const_iterator
    class ListIterator : public ListConstIterator {
//        friend list;
    public:
        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;


        ListIterator() : ListConstIterator(nullptr) {}

        explicit ListIterator(BaseNode *node) : ListConstIterator(node) {}

        reference operator*() const {
            return const_cast<reference>(ListConstIterator::operator*());
        }

        pointer operator->() const {
            return const_cast<pointer>(ListConstIterator::operator->());
        }

        ListIterator operator++() {
            ListConstIterator::operator++();
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator temp = *this;
            ListConstIterator::operator++();
            return temp;
        }

        ListIterator &operator--() {
            ListConstIterator::operator--();
            return *this;
        }

        ListIterator operator--(int) {
            ListIterator temp = *this;
            ListConstIterator::operator--();
            return temp;
        }
//    private:
//        const BaseNode* node_;
    };

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    using size_type = std::size_t;


    // List implementation
    list() : size_(0) {
        InitFantomNode();
    }

    void InitFantomNode() {
        fantom_node_ = new BaseNode();
        fantom_node_->prev = fantom_node_;
        fantom_node_->next = fantom_node_;
    }

    list(size_type n) : list() {
        if (n == 0) {
            throw std::out_of_range("Index out of range");
        }
        for (size_type i = 0; i < n; ++i) {
            push_back(T());
        }
    }

    list(const list &other) : list() {
        BaseNode *node = other.fantom_node_->next;
        while (node != other.fantom_node_) {
            push_back(node->data);
            node = node->next;
        }
        //foreach
    }


    list(std::initializer_list<value_type> const &items) noexcept
            : list() {
        for (value_type i: items) {
            push_back(i);
        }
    }

    list(list &&other) noexcept {
        if (this != &other) {

            size_ = other.size_;
            fantom_node_ = other.fantom_node_;
            other.size_ = 0;
            other.fantom_node_ = nullptr;
            other.InitFantomNode();
        }
    }

    ~list() {
        clear();
        delete fantom_node_;
    }


//    list& operator=(const list& other) {
//        if (this == &other) {
//            return *this;
//        }
//        clear();
//        for (const T& value : other) {
//            push_back(value);
//        }
//        return *this;
//    }

    list &operator=(list &&other) noexcept {
        while (fantom_node_ != fantom_node_) {
            pop_back();
        }
        fantom_node_ = other.fantom_node_;
        size_ = other.size_;
        other.size_ = 0;
        other.fantom_node_ = nullptr;
        other.InitFantomNode();
    }

    const_reference front() {
        return static_cast<Node *>(fantom_node_->next)->value;
    }

    const_reference back() {
        return static_cast<Node *>(fantom_node_->prev)->value;
    }

    iterator begin() {
        return iterator(fantom_node_->next);
    }

    iterator end() {
        return iterator(fantom_node_);
    }

//    const_iterator cbegin() const {
//        return const_iterator(fantom_node_->next);
//    }
//
//    const_iterator cend() const {
//        return const_iterator(fantom_node_);
//    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_type max_size() {
        return std::numeric_limits<size_t>::max() / sizeof(Node);
    }

    void clear() {
        while (size_ > 0) {
            pop_back();
        }
    }

    iterator insert(iterator pos, const_reference value) {

        Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_));
        Node *insert_node = new Node(value);

        if (next_node == fantom_node_->next) {
            insert_node->prev = fantom_node_;
            insert_node->next = next_node;
            next_node->prev = insert_node;
            fantom_node_->next = insert_node;
        } else {
            Node *prev_node = const_cast<Node *>(static_cast<const Node *>(next_node->prev)); // Узел перед позицией вставки
            prev_node->next = insert_node;
            insert_node->prev = prev_node;
            insert_node->next = next_node;
            next_node->prev = insert_node;
        }
        size_++;
        return iterator(insert_node);
    }

    void erase(iterator pos) {
        Node *prev_node = const_cast<Node *>(static_cast<const Node *>(pos.node_->prev));
        Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_->next));

        if (pos.node_ == fantom_node_) {
            return;
        }
        prev_node->next = next_node;
        next_node->prev = prev_node;
        delete pos.node_;
        size_--;

    }

    void push_back(const T &value) {
        Node *new_node = new Node(value);
        Node *prev_tail = static_cast<Node *>(fantom_node_->prev);
        prev_tail->next = new_node;
        new_node->prev = prev_tail;
        new_node->next = fantom_node_;
        fantom_node_->prev = new_node;
        ++size_;
    }

    void pop_back() {
        if (fantom_node_->prev != fantom_node_ || fantom_node_->next != fantom_node_) {
            Node *prev_tail = static_cast<Node *>(fantom_node_->prev);
            Node *new_tail = static_cast<Node *>(prev_tail->prev);
            new_tail->next = fantom_node_;
            fantom_node_->prev = new_tail;
            delete prev_tail;
            --size_;
        }
    }

    void push_front(const T &value) {

        Node *new_node = new Node(value);
        Node *next_head = static_cast<Node *>(fantom_node_->next);
        new_node->prev = next_head;
        new_node->next = next_head;

        next_head->prev = new_node;
        fantom_node_->next = new_node;

        ++size_;
    }

    void pop_front() {
        if (fantom_node_->prev != fantom_node_ || fantom_node_->next != fantom_node_) {
            Node *prev_head = static_cast<Node *>(fantom_node_->next);
            Node *new_head = static_cast<Node *>(prev_head->next);
            new_head->prev = fantom_node_;
            fantom_node_->next = new_head;
            delete prev_head;
            --size_;
        }
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

        Node *tmp = static_cast<Node *>(fantom_node_->next);
        Node *tmp_other = static_cast<Node *>(other.fantom_node_->next);

        while (tmp != fantom_node_ && tmp_other != other.fantom_node_) {
            if (tmp_other->value <= tmp->value) {
                Node *cur_tmp_other = tmp_other;
                tmp_other = static_cast<Node *>(tmp_other->next);


                tmp->prev->next = cur_tmp_other;
                cur_tmp_other->prev = tmp_other->prev;

                cur_tmp_other->next = tmp;
                tmp_other->prev = cur_tmp_other;


            } else {
                tmp = static_cast<Node *>(tmp->next);
            }
        }


        if (tmp_other != fantom_node_) {
            Node *this_last = static_cast<Node *>(fantom_node_->prev);

            this_last->next = tmp_other;
            tmp_other->prev = this_last;
            fantom_node_->prev = other.fantom_node_->prev;
            other.fantom_node_->prev->next = fantom_node_;
            size_ += other.size_;
        }


        size_ += other.size_;
        other.size_ = 0;
        other.fantom_node_ = nullptr;
        other.InitFantomNode();
    }


    void splice(const_iterator pos, list &other) {
        if (this == &other) {
            return; // Нельзя перемещать элементы из списка в самого себя
        }

        if (other.empty()) {
            return; // Нечего перемещать, если other пустой
        }

        // Узлы перед и после pos
        Node *prev_node = const_cast<Node *>(static_cast<const Node *>(pos.node_->prev));
        Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_));

        // Перемещаем все элементы из other в текущий список


        Node *other_first_node = const_cast<Node *>(static_cast<const Node *>(other.fantom_node_->next));
        Node *other_last_node = const_cast<Node *>(static_cast<const Node *>(other.fantom_node_->prev));

        prev_node->next = other_first_node;
        other_first_node->prev = prev_node;

        next_node->prev = other_last_node;
        other_last_node->next = next_node;

        size_ += other.size_;
        other.size_ = 0;

        other.InitFantomNode();
    }


    void reverse() noexcept {
        if (empty()) {
            return;
        }

        Node *fantom = static_cast<Node *>(fantom_node_);
        Node *first_node = static_cast<Node *>(fantom_node_->next);
        Node *last_node = static_cast<Node *>(fantom_node_->prev);

        Node *cur_node = first_node;
        while (cur_node != fantom) {
            Node *next_node = static_cast<Node *>(cur_node->next);
            cur_node->next = cur_node->prev;
            cur_node->prev = next_node;
            cur_node = next_node;
        }
        fantom_node_->next = last_node;
        fantom_node_->prev = first_node;

    }

    void unique() {
        if (size_ <= 1) {
            return; // Нечего удалять, если список пустой или содержит только один элемент
        }

        // Сортируем список перед применением unique
        //sort();

        Node* fantom = static_cast<Node*>(fantom_node_);
        Node* current = static_cast<Node*>(fantom_node_->next);

        while (current->next != fantom) {
            if (current->value == static_cast<Node*>(current->next)->value) {
                erase(iterator(current->next));
            } else {
                current = static_cast<Node*>(current->next);
            }
        }
    }

//    iterator insert_many(const_iterator pos, Args&&... args){
//
//    }
//
//    void insert_many_back(Args&&... args){
//
//    }
//
//    void insert_many_front(Args&&... args) {
//
//    }
private:
    size_type size_;
    BaseNode *fantom_node_;
};

#endif //CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
