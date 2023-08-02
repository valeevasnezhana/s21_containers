//
// Created by Tandra Ymir on 8/1/23.
//

#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H

#include "s21_list.h"

template<typename T>
class stack {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;


   stack() {

    }

    stack(std::initializer_list<value_type> const &items) noexcept{

    }

    stack(const stack &other) : stack() {

    }

    stack(stack &&other) noexcept {

    }

    ~stack() {

    }



    stack &operator=(stack &&other) noexcept {

    }

    const_reference top(){

    }

    bool empty() {

    }

    size_type size() {

    }

    void push(const_reference value) {

    }

    void pop() {

    }

    void swap(stack& other) {

    }
private:
    list <value_type> stack_;
};

#endif //CONTAINERS_STACK_H
