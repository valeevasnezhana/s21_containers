
#include "vector.h"
#include <vector>
#include <list>
#include <string>
#include "list.h"


int main()
{
//LIST-------------------------------------------------------------------------------------------
    list <int> l1;

    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(4);

    list <int> l2;

    l2.push_back(-1);
    l2.push_back(2);
    l2.push_back(15);
    l2.push_back(-5);
    l2.push_back(0);
    l2.push_back(8);
    l2.push_back(17);
    l2.push_back(5);




//    l1.insert(l1.end(),3);


//
//    std::cout<<*l1.begin()<<" ";
//    std::cout<<std::endl;
//
//
//
//
//    std::cout<<*(--l1.end())<<" ";
//    std::cout<<std::endl;

    list <int> l3;
//    l1.merge(l2);

//    l1.splice(++l1.begin(),l2);
    l1.reverse();

    l1.unique();
    for(auto &t:l1){
        std::cout<<t<<" ";
    }
    std::cout<<std::endl;

// l2.sort();

    for(auto &t:l2){
        std::cout<<t<<" ";
    }
    std::cout<<std::endl;



//VECTOR----------------------------------------------------------------------------------------
//T1

//s21::vector<std::string> str;
//
//
////T2
//
//s21::vector<std::string> str_1(5);
//    str_1[0] = "Z";
//    str_1[1] = "X";
//    str_1[2] = "C";
//    str_1[3] = "V";
//    str_1[4] = "B";
//    for(auto &i:str_1){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
//
//    //T3
//s21::vector<std::string> str_3{"ARA","BARA","SARA"};
//
//
//
//   //T4
//    s21::vector<std::string> str_2(str_1);
//    for(auto &i:str_1){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
//
////    //T5
//    s21::vector<std::string> str_8(std::move(str_2));
//    for(auto &i:str_8){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
//    //T6
//
//    str_2=str_3;
//    for(auto &i:str_2) {
//        std::cout << i << " ";
//    }
//    std::cout<<std::endl;
////    //T7
//    str=std::move(str_3);
//        for(auto &i:str) {
//            std::cout << i << " ";
//        }
//    std::cout<<std::endl;
//
//    //T8
//    s21::vector<std::string> str_6(5);
//    str_6[0] = "Z";
//    str_6[1] = "X";
//    str_6[2] = "C";
//    str_6[3] = "V";
//    str_6[4] = "B";
//
//    std::cout<<"[0]"<<str_6.at(0);
//    std::cout<<"[1]"<<str_6.at(1);
//    std::cout<<"[2]"<<str_6.at(2);
//    std::cout<<"[3]"<<str_6.at(3);
//    std::cout<<"[4]"<<str_6.at(4);
//    //std::cout<<"[5] "<<str_6.at(-1);
//    std::cout<<std::endl;
//
//    //T9
//    std::string *ptr = str_6.begin();
//    std::cout<<"pointer start "<<ptr<<std::endl;
//    std::string *ptr_e = str_6.end();
//    std::cout<<"pointer end "<<ptr_e<<std::endl;
//
//    //T10
//    std::cout<<"front "<<str_6.front()<<std::endl;
//    std::cout<<"back "<<str_6.back()<<std::endl;
//
//    //T11
//    std::cout<<"data is "<<str_6.data()<<std::endl;
//
//
//    //T12
//    std::cout<<"empty is "<<str_6.empty()<<std::endl;
//
//    //T13
//    std::cout<<"size is "<<str_6.size()<<std::endl;
//
//    //T14
//    std::cout<<"max_size is "<<str_6.max_size()<<std::endl;
//
//    //T15
//    str_6.pop_back();
//
//    //T16
//    //str_6.reserve("20");
//
//    //T14
//    std::cout<<"capacity is "<<str_6.capacity()<<std::endl;
//
//    //T15
//    str_6.shrink_to_fit();
//    std::cout<<"size is "<<str_6.size()<<std::endl;
//    std::cout<<"capacity is "<<str_6.capacity()<<std::endl;
//
//    for(auto &i:str){
//        std::cout<<i<<" move= ";
//    }
//    std::cout<<std::endl;
//
//
//    for(auto &i:str_2){
//        std::cout<<i<<" move ";
//    }
//    std::cout<<std::endl;
//
//    for(auto &i:str_1){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
//
//
//    for(auto &i:str_1){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
//
//    str.push_back("A");
//    str.push_back("B");
//    str.push_back("C");
//    str.insert(str.begin(),"D");
//
//    for(auto &i:str){
//        std::cout<<i<<" ";
//    }
//    std::cout<<std::endl;
}

