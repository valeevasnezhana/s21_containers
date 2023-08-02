
#include "s21_vector.h"
#include <vector>
#include <list>
#include <string>
#include "s21_containers.h"


int main() {

    s21::vector<int> vector_int{1, 2};
    s21::vector<int> vector_copy_int(std::move(vector_int));


    for(auto&v:vector_copy_int){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;

    std::cout<<vector_copy_int.size()<<" ";
    std::cout<<std::endl;

    std::cout<<vector_copy_int.capacity()<<" ";
    std::cout<<std::endl;

    s21::vector<std::string> vector_string{"I", "Groot"};
    s21::vector<std::string> vector_copy_string(std::move(vector_string));

    for(auto&v:vector_copy_string){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;

    std::cout<<vector_copy_string.size()<<" ";
    std::cout<<std::endl;

    std::cout<<vector_copy_string.capacity()<<" ";
    std::cout<<std::endl;
}

