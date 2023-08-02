#include <gtest/gtest.h>

#include <vector>
#include <array>
#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(vector_def_constructor, TEST_1) {
    s21::vector<int> vector_int;
    s21::vector<std::string> vector_string;

    EXPECT_EQ(vector_int.size(), 0);
    EXPECT_EQ(vector_int.capacity(), 0);

    EXPECT_EQ(vector_string.size(), 0);
    EXPECT_EQ(vector_string.capacity(), 0);
}


TEST(vector_itit_list_constructor, TEST_2) {
    s21::vector<int> vector_int{1, 2, 3, 4};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.size(), 4);
    EXPECT_EQ(vector_int.capacity(), 4);
    EXPECT_EQ(vector_int[0], 1);
    EXPECT_EQ(vector_int[1], 2);
    EXPECT_EQ(vector_int[2], 3);
    EXPECT_EQ(vector_int[3], 4);

    EXPECT_EQ(vector_string.size(), 2);
    EXPECT_EQ(vector_string.capacity(), 2);
    EXPECT_EQ(vector_string[0], "I");
    EXPECT_EQ(vector_string[1], "Groot");
}

TEST(vector_copy_constructor, TEST_3) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<int> vector_copy_int(vector_int);

    s21::vector<std::string> vector_string{"I", "Groot"};
    s21::vector<std::string> vector_copy_string(vector_string);

    EXPECT_EQ(vector_int.size(), vector_copy_int.size());
    EXPECT_EQ(vector_int.capacity(), vector_copy_int.capacity());
    EXPECT_EQ(vector_int[0], vector_copy_int[0]);
    EXPECT_EQ(vector_int[1], vector_copy_int[1]);

    EXPECT_EQ(vector_string.size(), vector_string.size());
    EXPECT_EQ(vector_string.capacity(), vector_string.capacity());
    EXPECT_EQ(vector_string[0], vector_string[0]);
    EXPECT_EQ(vector_string[1], vector_string[1]);
}

TEST(vector_move_constructor, TEST_4) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<int> vector_copy_int(std::move(vector_int));

    s21::vector<std::string> vector_string{"I", "Groot"};
    s21::vector<std::string> vector_copy_string(std::move(vector_string));


    EXPECT_EQ(vector_int.size(), 0);
    EXPECT_EQ(vector_copy_int.size(),2);
    EXPECT_EQ(vector_int.capacity(),0);
    EXPECT_EQ(vector_copy_int.capacity(),2);
    EXPECT_EQ(vector_copy_int[0], 1);
    EXPECT_EQ(vector_copy_int[1], 2);


    EXPECT_EQ(vector_string.size(), 0);
    EXPECT_EQ(vector_copy_string.size(),2);
    EXPECT_EQ(vector_string.capacity(),0);
    EXPECT_EQ( vector_copy_string.capacity(),2);
    EXPECT_EQ(vector_copy_string[0], "I");
    EXPECT_EQ(vector_copy_string[1], "Groot");

}

TEST(vector_eq_move, TEST_5) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<int> vector_copy_int;
    vector_copy_int = std::move(vector_int);


    s21::vector<std::string> vector_string{"I", "Groot"};
    s21::vector<std::string> vector_copy_string;
    vector_copy_string = std::move(vector_string);

    EXPECT_EQ(vector_int.size(), 0);
    EXPECT_EQ(vector_copy_int.size(),2);
    EXPECT_EQ(vector_int.capacity(),0);
    EXPECT_EQ(vector_copy_int.capacity(),2);
    EXPECT_EQ(vector_copy_int[0], 1);
    EXPECT_EQ(vector_copy_int[1], 2);


    EXPECT_EQ(vector_string.size(), 0);
    EXPECT_EQ(vector_copy_string.size(),2);
    EXPECT_EQ(vector_string.capacity(),0);
    EXPECT_EQ( vector_copy_string.capacity(),2);
    EXPECT_EQ(vector_copy_string[0], "I");
    EXPECT_EQ(vector_copy_string[1], "Groot");
}

TEST(vector_eq_copy, TEST_6) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<int> vector_copy_int;

    vector_copy_int = vector_int;

    s21::vector<std::string> vector_string{"I", "Groot"};
    s21::vector<std::string> vector_copy_string;
    vector_copy_string = vector_string;

    EXPECT_EQ(vector_int.size(), vector_copy_int.size());
    EXPECT_EQ(vector_int.capacity(), vector_copy_int.capacity());
    EXPECT_EQ(vector_int[0], vector_copy_int[0]);
    EXPECT_EQ(vector_int[1], vector_copy_int[1]);

    EXPECT_EQ(vector_string.size(), vector_string.size());
    EXPECT_EQ(vector_string.capacity(), vector_string.capacity());
    EXPECT_EQ(vector_string[0], vector_string[0]);
    EXPECT_EQ(vector_string[1], vector_string[1]);
}

TEST(vector_at, TEST_7) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.at(0), 1);
    EXPECT_EQ( vector_string.at(0), "I");
}

TEST(vector_at, TEST_8) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_ANY_THROW(vector_int.at(5));
    EXPECT_ANY_THROW(vector_string.at(5));
}


TEST(vector_square_braces, TEST_9) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int[1], 2);
    EXPECT_EQ(vector_string[1], "Groot");
}

TEST(vector_front, TEST_10) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.front(), 1);
    EXPECT_EQ(vector_string.front(), "I");
}

TEST(vector_back, TEST_11) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.back(), 2);
    EXPECT_EQ(vector_string.back(), "Groot");
}

TEST(vector_data, TEST_12) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.data(), &vector_int[0]);
    EXPECT_EQ(vector_string.data(), &vector_string[0]);
}


TEST(vector_begin, TEST_13) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.begin(), &vector_int[0]);
    EXPECT_EQ(vector_int.begin(), &vector_int[0]);
}

TEST(vector_end, TEST_14) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};


    EXPECT_EQ(vector_int.end(), &vector_int[0] + 2);
    EXPECT_EQ( vector_string.end(), &vector_string[0] + 2);
}

TEST(vector_empty, TEST_15) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.empty(), false);
    EXPECT_EQ(vector_string.empty(), false);
}

TEST(vector_empty, TEST_16) {
    s21::vector<int> vector_int{};
    s21::vector<std::string> vector_string{};

    EXPECT_EQ(vector_int.empty(), true);
    EXPECT_EQ(vector_string.empty(), true);
}

TEST(vector_size, TEST_17) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.size(), 2);
    EXPECT_EQ(vector_string.size(), 2);
}

TEST(vector_size, TEST_18) {
    s21::vector<int> vector_int{};
    s21::vector<std::string> vector_string{};

    EXPECT_EQ(vector_int.size(), 0);
    EXPECT_EQ(vector_string.size(), 0);
}

TEST(vector_max_size, TEST_19) {
    s21::vector<int> vector_int{1,2};
    std::vector<int> std_vec_int{1,2};

    s21::vector<std::string> vector_string{"Hello", ",", "world", "!"};
    std::vector<std::string> std_vec_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(vector_int.max_size(), std_vec_int.max_size());
    EXPECT_EQ(std_vec_string.max_size(), std_vec_string.max_size());
}

TEST(vector_reserve,  TEST_20) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.reserve(10);
    vector_string.reserve(10);

    EXPECT_EQ(vector_int.capacity(), 10);
    EXPECT_EQ(vector_string.capacity(), 10);
}

TEST(vector_capacity, TEST_21) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    EXPECT_EQ(vector_int.capacity(), 2);
    EXPECT_EQ(vector_string.capacity(), 2);
}

TEST(vector_capacity, TEST_22) {
    s21::vector<int> vector_int{};
    s21::vector<std::string> vector_string{};

    EXPECT_EQ(vector_int.capacity(), 0U);
    EXPECT_EQ(vector_string.capacity(), 0U);
}

TEST(vector_shrink_to_fit,TEST_23) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.reserve(20);
    vector_string.reserve(20);

    vector_int.shrink_to_fit();
    vector_string.shrink_to_fit();

    EXPECT_EQ(vector_int.capacity(),2);
    EXPECT_EQ(vector_string.capacity(), 2);
}

TEST(vector_shrink_to_fit, TEST_24) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.shrink_to_fit();
    vector_string.shrink_to_fit();

    EXPECT_EQ(vector_int.capacity(),2);
    EXPECT_EQ(vector_string.capacity(), 2);
}

TEST(vector_clear, TEST_25) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.clear();
    vector_string.clear();

    EXPECT_EQ(vector_int.size(), 0);
    EXPECT_EQ(vector_string.size(), 0);
}

TEST(vector_insert, TEST_26) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    auto pos_int = vector_int.begin() + 2;
    auto pos_string = vector_string.begin() + 2;

    vector_int.insert(pos_int, 3);
    vector_string.insert(pos_string, "!");

    EXPECT_EQ(vector_int[2], 3);

    EXPECT_EQ(vector_string[2], "!");
}

TEST(vector_erase, TEST_27) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    auto pos_int = vector_int.begin();
    auto pos_string = vector_string.begin();

    vector_int.erase(pos_int);
    vector_string.erase(pos_string);

    EXPECT_EQ(vector_int[0], 2);
    EXPECT_EQ(vector_string[0], "Groot");
}


TEST(vector_push_back, TEST_28) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.push_back(3);
    vector_string.push_back("!");

    EXPECT_EQ(*(vector_int.end() - 1), 3);
    EXPECT_EQ(*(vector_string.end() - 1), "!");
}


TEST(vector_pop_back, TEST_29) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    vector_int.pop_back();
    vector_string.pop_back();

    EXPECT_EQ(vector_int.size(), 1);
    EXPECT_EQ(vector_string.size(), 1);
}

TEST(vector_swap, TEST_30) {
    s21::vector<int> vector_int{1, 2};
    s21::vector<std::string> vector_string{"I", "Groot"};

    s21::vector<int> vector_int_sw{3, 4};
    s21::vector<std::string> vector_string_sw{"!", "!"};

    vector_int_sw.swap(vector_int);
    vector_string_sw.swap(vector_string);

    EXPECT_EQ( vector_string_sw.size(), 2);
    EXPECT_EQ( vector_string_sw.capacity(), 2);
    EXPECT_EQ( vector_string_sw[1], "Groot");

    EXPECT_EQ(vector_int.size(), 2);
    EXPECT_EQ(vector_int.capacity(), 2);
    EXPECT_EQ(vector_int[0], 3);
}

TEST(vector_insert_many, TEST_31) {
    s21::vector<int> vector_int{1, 4};
    s21::vector<std::string> vector_string{"Hello", ","};

    auto pos_int = vector_int.begin() + 1;
    auto pos_string = vector_string.begin() + 1;

    vector_int.insert_many(pos_int, 2, 3);
    vector_string.insert_many(pos_string, "world", "!");

    EXPECT_EQ(vector_int[1], 2);
    EXPECT_EQ(vector_int[2], 3);

    EXPECT_EQ(vector_string[1], "world");
    EXPECT_EQ(vector_string[2], "!");
}


TEST(vector_insert_many_back, TEST_32) {
    s21::vector<int> vector_int{1, 4};
    s21::vector<std::string> vector_string{"Hello", ","};

    vector_int.insert_many_back(2, 3);
    vector_string.insert_many_back("world", "!");

    EXPECT_EQ(vector_int[2], 2);
    EXPECT_EQ(vector_int[3], 3);

    EXPECT_EQ(vector_string[2], "world");
    EXPECT_EQ(vector_string[3], "!");

}

TEST(array_def_constructor, TEST_33) {
    s21::array<int, 4> array_int;
    s21::array<std::string, 4> array_string;

    EXPECT_EQ(array_int.size(), 4);
    EXPECT_EQ(array_string.size(), 4);
}

TEST(array_constructor, TEST_34) {
    s21::array<int,2> array_int{1, 2};
    s21::array<std::string,2> array_string{"I","Groot"};

    EXPECT_EQ(array_int.size(), 2);
    EXPECT_EQ(array_int[0], 1);

    EXPECT_EQ(array_string.size(), 2);
    EXPECT_EQ(array_string[0], "I");
}

TEST(array_copy_constructor,TEST_35) {


    s21::array<int,2> array_int{1, 2};
    s21::array<int, 2> arr_res_int(array_int);

    s21::array<std::string,2> array_string{"I","Groot"};
    s21::array<std::string, 2> array_res_string(array_string);

    EXPECT_EQ(array_int.size(), arr_res_int.size());
    EXPECT_EQ(array_int[0], arr_res_int[0]);
    EXPECT_EQ(array_int[1], arr_res_int[1]);

    EXPECT_EQ(array_string.size(), array_res_string.size());
    EXPECT_EQ(array_string[0], array_res_string[0]);
    EXPECT_EQ(array_string[1], array_res_string[1]);
}

TEST(array_move_constructor, TEST_36) {
    s21::array<int,2> array_int{1, 2};
    s21::array<int, 2> array_res_int = std::move(array_int);

    s21::array<std::string,2> array_string{"I","Groot"};
    s21::array<std::string, 2> array_res_string = std::move(array_string);

    EXPECT_EQ(array_res_int.size(), 2);
    EXPECT_EQ(array_res_int[0], 1);
    EXPECT_EQ(array_res_int[1], 2);

    EXPECT_EQ(array_res_string.size(), 2);
    EXPECT_EQ(array_res_string[0], "I");
    EXPECT_EQ(array_res_string[1], "Groot");

}

TEST(array_constructor, TEST_37) {
    s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
    s21::array<int, 4> s21_arr_res_int;
    s21_arr_res_int = std::move(s21_arr_ref_int);

    s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
    s21::array<double, 4> s21_arr_res_double;
    s21_arr_res_double = std::move(s21_arr_ref_double);

    s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
    s21::array<std::string, 4> s21_arr_res_string;
    s21_arr_res_string = std::move(s21_arr_ref_string);

    EXPECT_EQ(s21_arr_res_int.size(), 4U);
    EXPECT_EQ(s21_arr_res_int[0], 1);
    EXPECT_EQ(s21_arr_res_int[1], 4);
    EXPECT_EQ(s21_arr_res_int[2], 8);
    EXPECT_EQ(s21_arr_res_int[3], 9);

    EXPECT_EQ(s21_arr_res_double.size(), 4U);
    EXPECT_EQ(s21_arr_res_double[0], 1.4);
    EXPECT_EQ(s21_arr_res_double[1], 4.8);
    EXPECT_EQ(s21_arr_res_double[2], 8.9);
    EXPECT_EQ(s21_arr_res_double[3], 9.1);

    EXPECT_EQ(s21_arr_res_string.size(), 4U);
    EXPECT_EQ(s21_arr_res_string[0], "Hello");
    EXPECT_EQ(s21_arr_res_string[1], ",");
    EXPECT_EQ(s21_arr_res_string[2], "world");
    EXPECT_EQ(s21_arr_res_string[3], "!");
}

TEST(array_at, TEST_38) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.at(0), 1);
    EXPECT_EQ(s21_arr_double.at(0), 1.4);
    EXPECT_EQ(s21_arr_string.at(0), "Hello");
}

TEST(array_at, TEST_39) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_THROW(s21_arr_int.at(5), std::out_of_range);
    EXPECT_THROW(s21_arr_double.at(5), std::out_of_range);
    EXPECT_THROW(s21_arr_string.at(5), std::out_of_range);
}

TEST(array_at, TEST_40) {
    s21::array<int, 0> s21_arr_int;
    s21::array<double, 0> s21_arr_double;
    s21::array<std::string, 0> s21_arr_string;

    EXPECT_THROW(s21_arr_int.at(5), std::out_of_range);
    EXPECT_THROW(s21_arr_double.at(5), std::out_of_range);
    EXPECT_THROW(s21_arr_string.at(5), std::out_of_range);
}

TEST(array_square_braces, TEST_41) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int[1], 4);
    EXPECT_EQ(s21_arr_double[1], 4.8);
    EXPECT_EQ(s21_arr_string[0], "Hello");
}

TEST(array_front, TEST_42) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.front(), 1);
    EXPECT_EQ(s21_arr_double.front(), 1.4);
    EXPECT_EQ(s21_arr_string.front(), "Hello");
}

TEST(array_back, TEST_43) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.back(), 9);
    EXPECT_EQ(s21_arr_double.back(), 9.1);
    EXPECT_EQ(s21_arr_string.back(), "!");
}

TEST(array_data, TEST_44) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.data(), &s21_arr_int[0]);
    EXPECT_EQ(s21_arr_double.data(), &s21_arr_double[0]);
    EXPECT_EQ(s21_arr_string.data(), &s21_arr_string[0]);
}

TEST(array_begin, TEST_45) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.begin(), &s21_arr_int[0]);
    EXPECT_EQ(s21_arr_double.begin(), &s21_arr_double[0]);
    EXPECT_EQ(s21_arr_string.begin(), &s21_arr_string[0]);
}

TEST(array_end, TEST_46) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.end(), &s21_arr_int[0] + 4);
    EXPECT_EQ(s21_arr_double.end(), &s21_arr_double[0] + 4);
    EXPECT_EQ(s21_arr_string.end(), &s21_arr_string[0] + 4);
}

TEST(array_empty, TEST_47) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.empty(), 0);
    EXPECT_EQ(s21_arr_double.empty(), 0);
    EXPECT_EQ(s21_arr_string.empty(), 0);
}

TEST(array_empty, TEST_48) {
    s21::array<int, 0> s21_arr_int;
    s21::array<double, 0> s21_arr_double;
    s21::array<std::string, 0> s21_arr_string;

    EXPECT_EQ(s21_arr_int.empty(), 1);
    EXPECT_EQ(s21_arr_double.empty(), 1);
    EXPECT_EQ(s21_arr_string.empty(), 1);
}

TEST(array_size, TEST_49) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.size(), 4U);
    EXPECT_EQ(s21_arr_double.size(), 4U);
    EXPECT_EQ(s21_arr_string.size(), 4U);
}

TEST(array_size, TEST_50) {
    s21::array<int, 0> s21_arr_int;
    s21::array<double, 0> s21_arr_double;
    s21::array<std::string, 0> s21_arr_string;

    EXPECT_EQ(s21_arr_int.size(), 0U);
    EXPECT_EQ(s21_arr_double.size(), 0U);
    EXPECT_EQ(s21_arr_string.size(), 0U);
}

TEST(array_max_size, TEST_51) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    std::array<int, 4> std_arr_int{1, 4, 8, 9};

    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    std::array<double, 4> std_arr_double{1.4, 4.8, 8.9, 9.1};

    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};
    std::array<std::string, 4> std_arr_string{"Hello", ",", "world", "!"};

    EXPECT_EQ(s21_arr_int.max_size(), std_arr_int.max_size());
    EXPECT_EQ(s21_arr_double.max_size(), std_arr_double.max_size());
    EXPECT_EQ(s21_arr_string.max_size(), std_arr_string.max_size());
}

TEST(array_swap, TEST_52) {
    s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
    s21::array<int, 4> s21_arr_res_int{21, 21, 21, 21};

    s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
    s21::array<double, 4> s21_arr_res_double{21.0, 21.0, 21.0, 21.0};

    s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
    s21::array<std::string, 4> s21_arr_res_string{"21", "21", "21", "21"};

    s21_arr_ref_int.swap(s21_arr_res_int);
    s21_arr_ref_double.swap(s21_arr_res_double);
    s21_arr_ref_string.swap(s21_arr_res_string);

    EXPECT_EQ(s21_arr_ref_int[3], 21);
    EXPECT_EQ(s21_arr_res_int[0], 1);
    EXPECT_EQ(s21_arr_res_int[1], 4);
    EXPECT_EQ(s21_arr_res_int[2], 8);
    EXPECT_EQ(s21_arr_res_int[3], 9);

    EXPECT_EQ(s21_arr_ref_double[3], 21.0);
    EXPECT_EQ(s21_arr_res_double[0], 1.4);
    EXPECT_EQ(s21_arr_res_double[1], 4.8);
    EXPECT_EQ(s21_arr_res_double[2], 8.9);
    EXPECT_EQ(s21_arr_res_double[3], 9.1);

    EXPECT_EQ(s21_arr_ref_string[3], "21");
    EXPECT_EQ(s21_arr_res_string[0], "Hello");
    EXPECT_EQ(s21_arr_res_string[1], ",");
    EXPECT_EQ(s21_arr_res_string[2], "world");
    EXPECT_EQ(s21_arr_res_string[3], "!");
}

TEST(array_fill, TEST_53) {
    s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
    s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
    s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

    s21_arr_int.fill(21);
    s21_arr_double.fill(21.0);
    s21_arr_string.fill("21");

    EXPECT_EQ(s21_arr_int[0], 21);
    EXPECT_EQ(s21_arr_int[1], 21);
    EXPECT_EQ(s21_arr_int[2], 21);
    EXPECT_EQ(s21_arr_int[3], 21);

    EXPECT_EQ(s21_arr_double[0], 21.0);
    EXPECT_EQ(s21_arr_double[1], 21.0);
    EXPECT_EQ(s21_arr_double[2], 21.0);
    EXPECT_EQ(s21_arr_double[3], 21.0);

    EXPECT_EQ(s21_arr_string[0], "21");
    EXPECT_EQ(s21_arr_string[1], "21");
    EXPECT_EQ(s21_arr_string[2], "21");
    EXPECT_EQ(s21_arr_string[3], "21");
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
