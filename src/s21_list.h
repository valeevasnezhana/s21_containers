//
// Created by Tandra Ymir on 7/27/23.
//

#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include <limits>
#include <iostream>
#include <initializer_list>

namespace s21 {
    template <typename T>
    class list {
    public: class ListIterator;
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
            friend class list<T>;

        public:
            using value_type = T;
            using reference = T &;
            using const_reference = const T&;
            using const_pointer = const T *;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            ListConstIterator() : node_() {}

            explicit ListConstIterator(BaseNode *node) : node_(node) {}
            ListConstIterator(ListIterator iter){
                node_=iter.node_;
            }

            const_reference operator*() const {
                return static_cast<Node *>(node_)->value;
            }

            const_pointer operator->() const {
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
            BaseNode *node_;
        };

        class ListIterator {
            friend list;
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            ListIterator() : node_() {}

            explicit ListIterator(BaseNode *node) : node_(node) {}

            ListIterator (ListConstIterator iter) {
                node_=iter.node_;
            }

            reference operator*() const {
                return static_cast<Node*>(node_)->value;
            }

            pointer operator->() const {
                return &(static_cast<Node *>(node_)->value);
            }

            ListIterator &operator++() {
                node_ = node_->next;
                return *this;
            }

            ListIterator operator++(int) {
                ListConstIterator temp = *this;
                node_ = node_->next;
                return temp;
            }

            ListIterator &operator--() {
                node_ = node_->prev;
                return *this;
            }

            ListIterator operator--(int) {
                ListConstIterator temp = *this;
                node_ = node_->prev;
                return temp;
            }

            bool operator==(const ListIterator &other) const {
                return node_ == other.node_;
            }

            bool operator!=(const ListIterator &other) const {
                return node_ != other.node_;
            }

        private:
            BaseNode *node_;
        };


        using value_type = T;
        using reference = T&;
        using const_reference = const T &;
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;
        using size_type = std::size_t;


        list() : size_(0) {
            fantom_node_ = new BaseNode();
            fantom_node_->prev = fantom_node_;
            fantom_node_->next = fantom_node_;
        }


        explicit list(size_type n) : list() {
            for (size_type i = 0; i < n; ++i) {
                push_back(T());
            }
        }

        explicit list(std::initializer_list<value_type> const &items) noexcept : list() {
            for (const_reference value : items) {
                push_back(value);
            }
        }

        list(const list &other) : list() {
            for (const_reference value : other) {
                push_back(value);
            }
        }

        list(list &&other) noexcept {
            size_ = other.size_;
            fantom_node_ = other.fantom_node_;
            other.size_ = 0;
            other.fantom_node_ = nullptr;
        }

        ~list() {
            while (!empty()) {
                if (fantom_node_->prev != fantom_node_) {
                    Node *prev_tail = static_cast<Node *>(fantom_node_->prev);
                    Node *new_tail = static_cast<Node *>(prev_tail->prev);
                    new_tail->next = fantom_node_;
                    fantom_node_->prev = new_tail;
                    delete prev_tail;
                    --size_;
                }
            }
            delete fantom_node_;
        }

        list& operator=(const list& other) {
            if (this == &other) {
                return *this;
            }
            clear();
            for (const T& value : other) {
                push_back(value);
            }
            return *this;
        }

        list &operator=(list &&other) noexcept {
            while (!empty()) {
                pop_back();
            }
            fantom_node_ = other.fantom_node_;
            size_ = other.size_;
            other.size_ = 0;
            other.fantom_node_ = nullptr;
            return *this;
        }

        const_reference front() const {
            return static_cast<Node *>(fantom_node_->next)->value;
        }

        const_reference back() const {
            return static_cast<Node *>(fantom_node_->prev)->value;
        }

        iterator begin() { return iterator(fantom_node_->next); }

        iterator end() { return iterator(fantom_node_); }

        const_iterator begin() const { return const_iterator(fantom_node_->next); }

        const_iterator end() const { return const_iterator(fantom_node_); }

        bool empty() const noexcept { return size_ == 0; }

        size_t size() const noexcept{ return size_; }

        size_type max_size() const noexcept{
            return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
        }

        void clear() noexcept{
            while (size_ > 0) {
                pop_back();
            }
        }

        iterator insert(iterator pos, const_reference value) {
            Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_));
            Node *insert_node = new Node(value);

            next_node->prev->next = insert_node;
            insert_node->prev = next_node->prev;
            next_node->prev = insert_node;
            insert_node->next = next_node;

            ++size_;
            return iterator(insert_node);
        }

        void erase(iterator pos) {
            Node *prev_node =
                    const_cast<Node *>(static_cast<const Node *>(pos.node_->prev));
            Node *next_node =
                    const_cast<Node *>(static_cast<const Node *>(pos.node_->next));

            if (pos.node_ == fantom_node_) {
                return;
            }
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete pos.node_;
            --size_;
        }

        void push_back(const_reference value) {
            Node *new_node = new Node(value);
            Node *prev_tail = static_cast<Node *>(fantom_node_->prev);
            prev_tail->next = new_node;
            new_node->prev = prev_tail;
            new_node->next = fantom_node_;
            fantom_node_->prev = new_node;
            ++size_;
        }

        void pop_back() {
            Node *prev_tail = static_cast<Node *>(fantom_node_->prev);
            Node *new_tail = static_cast<Node *>(prev_tail->prev);
            new_tail->next = fantom_node_;
            fantom_node_->prev = new_tail;
            delete prev_tail;
            --size_;
        }

        void push_front(const_reference value) {
            Node *new_node = new Node(value);
            Node *next_head = static_cast<Node *>(fantom_node_->next);
            new_node->prev = next_head;
            new_node->next = next_head;

            next_head->prev = new_node;
            fantom_node_->next = new_node;

            ++size_;
        }

        void pop_front() {
            Node *prev_head = static_cast<Node *>(fantom_node_->next);
            Node *new_head = static_cast<Node *>(prev_head->next);
            new_head->prev = fantom_node_;
            fantom_node_->next = new_head;
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

            Node *this_node = static_cast<Node *>(fantom_node_->next);
            Node *other_node = static_cast<Node *>(other.fantom_node_->next);

            while (this_node != fantom_node_ && other_node != other.fantom_node_) {
                if (other_node->value <= this_node->value) {
                    Node *cur_other_node = other_node;
                    other_node = static_cast<Node *>(other_node->next);

                    cur_other_node->prev = this_node->prev;
                    cur_other_node->next = this_node;
                    this_node->prev->next = cur_other_node;
                    this_node->prev = cur_other_node;

                } else {
                    this_node = static_cast<Node *>(this_node->next);
                }
            }

            if (other_node != other.fantom_node_) {
                Node *this_last = static_cast<Node *>(fantom_node_->prev);

                this_last->next = other_node;
                other_node->prev = this_last;
                fantom_node_->prev = other.fantom_node_->prev;
                other.fantom_node_->prev->next = fantom_node_;
            }

            size_ += other.size_;
            other.size_ = 0;
            other.fantom_node_= nullptr;
        }

        void splice(const_iterator pos, list &other) {
            if (this == &other) {
                return;
            }

            if (other.empty()) {
                return;
            }


            Node *prev_node =
                    const_cast<Node *>(static_cast<const Node *>(pos.node_->prev));
            Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_));

            Node *other_first_node =
                    const_cast<Node *>(static_cast<const Node *>(other.fantom_node_->next));
            Node *other_last_node =
                    const_cast<Node *>(static_cast<const Node *>(other.fantom_node_->prev));

            prev_node->next = other_first_node;
            other_first_node->prev = prev_node;

            next_node->prev = other_last_node;
            other_last_node->next = next_node;

            size_ += other.size_;
            other.size_ = 0;
            other.fantom_node_=nullptr;
        }

        void reverse() noexcept {
            if (size()<2) {
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
                return;
            }

            Node *fantom = static_cast<Node *>(fantom_node_);
            Node *current = static_cast<Node *>(fantom_node_->next);

            while (current->next != fantom) {
                if (current->value == static_cast<Node *>(current->next)->value) {
                    erase(iterator(current->next));
                } else {
                    current = static_cast<Node *>(current->next);
                }
            }
        }

        void sort() {
            if (size_ <= 1) {
                return;
            }
            list left_half;
            list right_half;
            Node *cur_node = static_cast<Node *>(fantom_node_->next);
            size_type middle = size_ / 2;
            for (size_type i = 0; i < middle; ++i) {
                left_half.push_back(cur_node->value);
                cur_node = static_cast<Node *>(cur_node->next);
            }
            for (size_t i = middle; i < size_; ++i) {
                right_half.push_back(cur_node->value);
                cur_node = static_cast<Node *>(cur_node->next);
            }
            clear();

            left_half.sort();
            right_half.sort();

            merge(left_half);
            merge(right_half);
        }

        template <typename... Args>
        iterator insert_many(const_iterator pos, Args &&...args) {

            Node *prev_node =
                    const_cast<Node *>(static_cast<const Node *>(pos.node_->prev));
            Node *next_node = const_cast<Node *>(static_cast<const Node *>(pos.node_));

            list<value_type> init_list{std::forward<Args>(args)...};
            prev_node->next = init_list.fantom_node_->next;
            next_node->prev = init_list.fantom_node_->prev;
            init_list.fantom_node_->next->prev = prev_node;
            init_list.fantom_node_->prev->next = next_node;

            size_ += init_list.size();

            init_list.size_ = 0;
            init_list.ValidFantomNode();

            return iterator(prev_node->next);
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
        void ValidFantomNode(){
            fantom_node_->prev = fantom_node_;
            fantom_node_->next = fantom_node_;
        }
        size_type size_;
        BaseNode *fantom_node_;
    };
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
