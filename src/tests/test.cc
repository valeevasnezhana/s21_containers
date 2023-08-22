#include <gtest/gtest.h>

#include <array>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

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
  EXPECT_EQ(vector_copy_int.size(), 2);
  EXPECT_EQ(vector_int.capacity(), 0);
  EXPECT_EQ(vector_copy_int.capacity(), 2);
  EXPECT_EQ(vector_copy_int[0], 1);
  EXPECT_EQ(vector_copy_int[1], 2);

  EXPECT_EQ(vector_string.size(), 0);
  EXPECT_EQ(vector_copy_string.size(), 2);
  EXPECT_EQ(vector_string.capacity(), 0);
  EXPECT_EQ(vector_copy_string.capacity(), 2);
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
  EXPECT_EQ(vector_copy_int.size(), 2);
  EXPECT_EQ(vector_int.capacity(), 0);
  EXPECT_EQ(vector_copy_int.capacity(), 2);
  EXPECT_EQ(vector_copy_int[0], 1);
  EXPECT_EQ(vector_copy_int[1], 2);

  EXPECT_EQ(vector_string.size(), 0);
  EXPECT_EQ(vector_copy_string.size(), 2);
  EXPECT_EQ(vector_string.capacity(), 0);
  EXPECT_EQ(vector_copy_string.capacity(), 2);
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
  EXPECT_EQ(vector_string.at(0), "I");
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
  EXPECT_EQ(vector_string.end(), &vector_string[0] + 2);
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

// TEST(vector_max_size, TEST_19) {
//   s21::vector<int> vector_int{1, 2};
//   std::vector<int> std_vec_int{1, 2};
//
//   s21::vector<std::string> vector_string{"Hello", ",", "world", "!"};
//   std::vector<std::string> std_vec_string{"Hello", ",", "world", "!"};
//
//   EXPECT_EQ(vector_int.max_size(), std_vec_int.max_size());
//   EXPECT_EQ(std_vec_string.max_size(), std_vec_string.max_size());
// }

TEST(vector_reserve, TEST_20) {
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

TEST(vector_shrink_to_fit, TEST_23) {
  s21::vector<int> vector_int{1, 2};
  s21::vector<std::string> vector_string{"I", "Groot"};

  vector_int.reserve(20);
  vector_string.reserve(20);

  vector_int.shrink_to_fit();
  vector_string.shrink_to_fit();

  EXPECT_EQ(vector_int.capacity(), 2);
  EXPECT_EQ(vector_string.capacity(), 2);
}

TEST(vector_shrink_to_fit, TEST_24) {
  s21::vector<int> vector_int{1, 2};
  s21::vector<std::string> vector_string{"I", "Groot"};

  vector_int.shrink_to_fit();
  vector_string.shrink_to_fit();

  EXPECT_EQ(vector_int.capacity(), 2);
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

  EXPECT_EQ(vector_string_sw.size(), 2);
  EXPECT_EQ(vector_string_sw.capacity(), 2);
  EXPECT_EQ(vector_string_sw[1], "Groot");

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
  s21::array<int, 2> array_int{1, 2};
  s21::array<std::string, 2> array_string{"I", "Groot"};

  EXPECT_EQ(array_int.size(), 2);
  EXPECT_EQ(array_int[0], 1);

  EXPECT_EQ(array_string.size(), 2);
  EXPECT_EQ(array_string[0], "I");
}

TEST(array_copy_constructor, TEST_35) {
  s21::array<int, 2> array_int{1, 2};
  s21::array<int, 2> arr_res_int(array_int);

  s21::array<std::string, 2> array_string{"I", "Groot"};
  s21::array<std::string, 2> array_res_string(array_string);

  EXPECT_EQ(array_int.size(), arr_res_int.size());
  EXPECT_EQ(array_int[0], arr_res_int[0]);
  EXPECT_EQ(array_int[1], arr_res_int[1]);

  EXPECT_EQ(array_string.size(), array_res_string.size());
  EXPECT_EQ(array_string[0], array_res_string[0]);
  EXPECT_EQ(array_string[1], array_res_string[1]);
}

TEST(array_move_constructor, TEST_36) {
  s21::array<int, 2> array_int{1, 2};
  s21::array<int, 2> array_res_int = std::move(array_int);

  s21::array<std::string, 2> array_string{"I", "Groot"};
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

TEST(list_construct, TEST_54) {
  s21::list<int> s21_list_int;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_string.size(), 0);
}

TEST(list_construct_two, TEST_55) {
  s21::list<int> s21_list_int(5);
  s21::list<std::string> s21_list_string(5);
  EXPECT_EQ(s21_list_int.size(), 5);
  EXPECT_EQ(s21_list_string.size(), 5);
}

TEST(list_construct_many, TEST_56) {
  s21::list<int> s21_list_int{1, 2, 3, 4};

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};

  EXPECT_EQ(s21_list_int.size(), 4);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 4);
  EXPECT_EQ(s21_list_string.front(), "I");
}

TEST(list_construct_copy, TEST_57) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int(s21_list_int);

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string(s21_list_string);

  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(list_copy_operator, TEST_58) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int = s21_list_int;

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string = s21_list_string;

  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(list_copy_operator_zero, TEST_59) {
  s21::list<int> s21_list_int;
  s21::list<int> s21_list_res_int = s21_list_int;

  s21::list<std::string> s21_list_string;
  s21::list<std::string> s21_list_res_string = s21_list_string;

  EXPECT_EQ(s21_list_res_int.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 0);
}

TEST(list_operator_move, TEST_60) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int = std::move(s21_list_int);

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string = std::move(s21_list_string);

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(list_construct_move, TEST_61) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int;
  s21_list_res_int = std::move(s21_list_int);

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string;
  s21_list_res_string = std::move(s21_list_string);

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(list_move, TEST_62) {
  s21::list<int> a{43, 43, 43, 5};
  s21::list<int> b{1};
  a = std::move(b);
  EXPECT_EQ(a.back(), 1);
}

// TEST(list_max_size, TEST_62) {
//   size_t n = 1;
//   s21::list<int> list(n);
//   std::list<int> list_orig(n);
//
//   EXPECT_EQ(list.max_size(), list_orig.max_size());
// }

TEST(list_pop_front, TEST_62) {
  s21::list<int> list{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.front(), 1);
  list.pop_front();
  EXPECT_EQ(list.front(), 2);
  list.pop_front();
  EXPECT_EQ(list.front(), 3);
  list.pop_front();
  EXPECT_EQ(list.front(), 4);
  EXPECT_EQ(list.size(), 3);

  s21::list<std::string> list_str{"1", "2", "3", "4", "5", "6"};
  EXPECT_EQ(list_str.size(), 6);
  EXPECT_EQ(list_str.front(), "1");
  list_str.pop_front();
  EXPECT_EQ(list_str.front(), "2");
  list_str.pop_front();
  EXPECT_EQ(list_str.front(), "3");
  list_str.pop_front();
  EXPECT_EQ(list_str.front(), "4");
  EXPECT_EQ(list_str.size(), 3);
}

TEST(list_pop_back, TEST_63) {
  s21::list<int> list{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.back(), 6);
  list.pop_back();
  EXPECT_EQ(list.back(), 5);
  list.pop_back();
  EXPECT_EQ(list.back(), 4);
  list.pop_back();
  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(list.size(), 3);
}

TEST(list_push_front, TEST_66) {
  s21::list<int> s21_list_int{1, 2, 3, 4, 5, 6};
  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};

  s21_list_int.push_front(7);
  s21_list_string.push_front("7");

  EXPECT_EQ(s21_list_int.size(), 7);
  EXPECT_EQ(s21_list_int.front(), 7);

  EXPECT_EQ(s21_list_string.size(), 5);
  EXPECT_EQ(s21_list_string.front(), "7");
}

TEST(empty_list_push_front, TEST_67) {
  s21::list<int> s21_list_int;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_front(1);
  s21_list_string.push_front("1");

  EXPECT_EQ(s21_list_int.size(), 1);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 1);
  EXPECT_EQ(s21_list_string.front(), "1");
}

TEST(one_arg_list_push_front, TEST_68) {
  s21::list<int> s21_list_int{1};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_front(1);
  s21_list_string.push_front("1");

  EXPECT_EQ(s21_list_int.size(), 2);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 2);
  EXPECT_EQ(s21_list_string.front(), "1");
}

TEST(many_arg_list_push_front, TEST_69) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7};
  std::list<int> list_orig{1, 2, 3, 4, 5, 6, 7};
  list.push_front(20);
  list_orig.push_front(20);
  auto itr_orig = list_orig.begin();
  for (auto itr = list.begin(); itr != list.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig++);
  }

  s21::list<int> list_two;
  std::list<int> list_orig_two;
  list_two.push_front(21);
  list_orig_two.push_front(21);
  auto itr_orig_two = list_orig_two.begin();
  for (auto itr_two = list_two.begin(); itr_two != list_two.end(); itr_two++) {
    EXPECT_EQ(*itr_two, *itr_orig_two++);
  }
}

TEST(list_push_back, TEST_71) {
  s21::list<int> s21_list_int{1, 2, 3, 4, 5, 6};
  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};

  s21_list_int.push_back(33);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 7);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_string.size(), 5);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(zero_arg_list_push_back, TEST_72) {
  s21::list<int> s21_list_int;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_back(33);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 1);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_string.size(), 1);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(one_arg_list_push_back, TEST_73) {
  s21::list<int> s21_list_int{1};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_back(33);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 2);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_string.size(), 2);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(list_pop_front, TEST_74) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7};
  std::list<int> list_orig = {1, 2, 3, 4, 5, 6, 7};
  list.pop_front();
  list_orig.pop_front();
  auto itr_orig = list_orig.begin();
  for (auto itr = list.begin(); itr != list.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig++);
  }
}

TEST(list_pop_front, TEST_75) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};

  s21_list_int.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 3);
  EXPECT_EQ(s21_list_int.back(), 3);
  EXPECT_EQ(s21_list_string.size(), 3);
  EXPECT_EQ(s21_list_string.back(), "Groot");
}

TEST(list_back, TEST_76) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  EXPECT_EQ(s21_list_int.back(), 4);
  EXPECT_EQ(s21_list_string.back(), "!");
}

TEST(list_swap, TEST_77) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int{12, 13};

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_int.swap(s21_list_res_int);
  s21_list_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.front(), 12);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 4U);
  EXPECT_EQ(s21_list_string.front(), "12");
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(list_swap, TEST_78) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<int> s21_list_res_int;

  s21::list<std::string> s21_list_string{"I", "m", "Groot", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_res_int.swap(s21_list_int);
  s21_list_res_string.swap(s21_list_string);

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_string.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "I");
}

TEST(zero_list_sort, TEST_79) {
  s21::list<int> s21_list_int{4, 3, 2, 1};
  s21::list<std::string> s21_list_string{"I", "m", "Groot", "A"};

  s21_list_int.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_string.front(), "A");
}

TEST(one_arg_list_sort, TEST_79) {
  s21::list<int> s21_list_int{1};
  s21::list<std::string> s21_list_string{"I"};

  s21_list_int.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_string.front(), "I");
}

TEST(list_merge, TEST_80) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{12, 13};

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 6);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_string.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 8);
  EXPECT_EQ(s21_list_res_string.front(), "12");
}

TEST(empty_list_merge, TEST_81) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_string.size(), 0);
  EXPECT_EQ(s21_list_res_string.size(), 4);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(list_reverse, TEST_82) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "A"};

  s21_list_int.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 4);
  EXPECT_EQ(s21_list_string.front(), "A");
}

TEST(one_arg_list_reverse, TEST_83) {
  s21::list<int> s21_list_int{1};
  s21::list<std::string> s21_list_string{"Hello"};

  s21_list_int.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(list_unique, TEST_84) {
  s21::list<int> s21_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};
  s21::list<std::string> s21_list_string{"Hello", ",",     "Hello", ",",
                                         "world", ",",     "world", "!",
                                         "!",     "world", "!"};

  s21_list_int.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4);
  EXPECT_EQ(s21_list_string.size(), 10);
}

TEST(list_unique_two, TEST_85) {
  s21::list<int> s21_list_int;
  s21::list<std::string> s21_list_string;

  s21_list_int.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_string.size(), 0);
}

TEST(list_size, TEST_86) {
  s21::list<int> s21_list_int{1, 2, 3, 4};

  EXPECT_EQ(s21_list_int.size(), 4);
}

TEST(size, TEST_87) {
  s21::list<int> s21_list_int;
  EXPECT_EQ(s21_list_int.size(), 0U);
}

TEST(list_empty, TEST_88) {
  s21::list<int> s21_list_int{1, 2, 3, 4};
  EXPECT_EQ(s21_list_int.empty(), 0);
}

// TEST(list_empty, TEST_89) {
//   std::list<int> orig_list(5);
//   s21::list<int> lst(5);
//   auto orig_itr = orig_list.end();
//   auto itr = lst.end();
//   EXPECT_EQ(*orig_itr, *itr);
// }

TEST(list_insert, TEST_90) {
  s21::list<int> s21_list_int{1, 4, 8, 9};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);
  EXPECT_EQ(*(++s21_list_int.begin()), 1);
}

TEST(empty_list_insert, TEST_91) {
  s21::list<std::string> s21_list_string;

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(empty_list_insert, TEST_92) {
  s21::list<int> s21_list_int{1};
  s21::list<std::string> s21_list_string{"1"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(list_splice, TEST_93) {
  s21::list<int> s21_list_ref_int{3, 5};
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<std::string> s21_list_ref_string{"Hi"};
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 3);
  EXPECT_EQ(*(++s21_list_res_int.begin()), 5);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hi");
}

TEST(list_splice, TEST_94) {
  s21::list<int> s21_list_ref_int;
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<std::string> s21_list_ref_string;
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hello");
}

TEST(list_splice, TEST_95) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);
}

TEST(list_insert_many_back, TEST_96) {
  s21::list<int> list{1, 2, 3, 4, 5};
  list.insert_many_back(6, 7, 8);
  EXPECT_EQ(list.back(), 8);
}

TEST(list_insert_many_back, TEST_97) {
  s21::list<int> list;
  list.insert_many_back(4, 5, 6);
  EXPECT_EQ(list.back(), 6);
  EXPECT_EQ(list.front(), 4);
}

TEST(list_insert_many_front, TEST_98) {
  s21::list<int> list{1, 2, 3, 4, 5};
  list.insert_many_front(6, 7, 8);
  EXPECT_EQ(list.front(), 6);
}

TEST(list_insert_many_front, TEST_99) {
  s21::list<int> list;
  list.insert_many_front(4, 5, 6);
  EXPECT_EQ(list.front(), 4);
  EXPECT_EQ(list.back(), 6);
}

TEST(list_iterator, TEST_100) {
  s21::list<int> list{1, 2, 3, 4};
  std::list<int> list_org = {1, 2, 3, 4};
  unsigned int n = list.size();
  unsigned int n_orig = list_org.size();
  EXPECT_EQ(n, n_orig);

  auto itr = list.begin();
  auto itr_orig = list_org.begin();
  auto end = list.end();
  auto end_orig = list_org.end();
  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr++;
    itr_orig++;
  }
}

TEST(list_iterator, TEST_101) {
  s21::list<int> list{1, 2, 3, 4};
  std::list<int> list_org = {1, 2, 3, 4};
  unsigned int n = list.size();
  unsigned int n_orig = list_org.size();
  EXPECT_EQ(n, n_orig);

  auto itr = list.begin();
  auto itr_orig = list_org.begin();
  auto end = list.end();
  auto end_orig = list_org.end();

  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr--;
    itr_orig--;
  }
}

TEST(list_iterator, TEST_102) {
  s21::list<int> list{1, 2, 3, 4};
  auto itr = ++list.begin();
  EXPECT_EQ(*itr, 2);
}

TEST(list_iterator, TEST_103) {
  s21::list<int> list{1, 2, 3, 4};
  auto itr = --list.end();
  s21::list<int> list_org{1, 2, 3, 4};
  auto itr_org = --list_org.end();
  EXPECT_EQ(*itr, *itr_org);
}

TEST(list_iterator, TEST_104) {
  s21::list<int> list{1, 2, 3, 4};
  auto itr = list.end();
  --itr;
  EXPECT_EQ(*itr, 4);
}

TEST(empty_list_insert, TEST_105) {
  s21::list<int> empty_list;
  empty_list.insert(empty_list.begin(), 4);
  EXPECT_EQ(empty_list.front(), 4);
}

TEST(empty_list_insert_many, TEST_106) {
  s21::list<int> empty_list;
  empty_list.insert_many(empty_list.begin(), 1, 2, 3, 4);
  EXPECT_EQ(empty_list.front(), 1);
  EXPECT_EQ(empty_list.back(), 4);
}

TEST(list_insert, TEST_107) {
  s21::list<int> s21_list_int{1, 2, 3, 4, 5, 6, 7, 8};

  auto it_int = s21_list_int.begin();
  for (unsigned int i = 0; i < 5; i++) {
    ++it_int;
  }
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(*(it_int), 13);
}

TEST(list_reverse, TEST_108) {
  s21::list<int> s21_list_int;
  s21_list_int.reverse();
  EXPECT_EQ(s21_list_int.empty(), true);
}

TEST(list_splice, TEST_109) {
  s21::list<int> s21_list_res_int{1, 4, 8, 9};
  s21_list_res_int.splice(s21_list_res_int.begin(), s21_list_res_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);
}

// TEST(list_merge,  TEST_110) {
//   s21::list<int> s21_list_int{1, 4, 8, 9};
//   s21_list_int.merge(s21_list_int);
//   EXPECT_EQ(*(s21_list_int.begin()),1);
// }

// TEST(list_merge,  TEST_111) {
//   s21::list<int> s21_list_int{1, 4, 8, 9};
//   s21::list<int> s21_list_int_empty;
//   s21_list_int.merge(s21_list_int_empty);
//   EXPECT_EQ(*(s21_list_int.begin()),1);
// }
// TEST(list_erase,  TEST_112) {
//   s21::list<int> s21_list_int_empty;
//   EXPECT_EQ(s21_list_int_empty.empty(),true);
// }

TEST(stack_arg_constructor, TEST_113) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<std::string> s21_stack_string{"1", "2", "3", "4", "5"};

  EXPECT_EQ(s21_stack_int.size(), 5);
  EXPECT_EQ(s21_stack_int.top(), 5);

  EXPECT_EQ(s21_stack_string.size(), 5);
  EXPECT_EQ(s21_stack_string.top(), "5");
}

TEST(stack_copy_constructor, TEST_114) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int(s21_stack_int);

  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}

TEST(stack_operator_copy_constructor, TEST_115) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int = s21_stack_int;

  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}

TEST(stack_operator_move_constructor, TEST_116) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int = std::move(s21_stack_int);

  EXPECT_EQ(s21_stack_int.size(), 0);
  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}

TEST(stack_operator_move_move_constructor, TEST_117) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int;
  s21_stack_res_int = std::move(s21_stack_int);

  EXPECT_EQ(s21_stack_int.size(), 0);
  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}

TEST(stack_empty, TEST_118) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_stack_int.empty(), 0);
}

TEST(stack_empty, TEST_119) {
  s21::stack<int> s21_stack_int;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.empty(), true);
  EXPECT_EQ(s21_stack_string.empty(), true);
}

TEST(stack_empty, TEST_120) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_stack_int.size(), 5U);
}

TEST(stack_top, TEST_121) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_stack_int.top(), 5);
}

TEST(stack_push, TEST_122) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21_stack_int.push(6);
  EXPECT_EQ(s21_stack_int.top(), 6);
}

TEST(stack_push, TEST_123) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.push(1);
  EXPECT_EQ(s21_stack_int.top(), 1);
}

TEST(stack_pop, TEST_124) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21_stack_int.pop();

  EXPECT_EQ(s21_stack_int.top(), 4);
}

TEST(stack_swap, TEST_125) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int;

  s21_stack_int.swap(s21_stack_res_int);

  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_int.size(), 0);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}

TEST(stack_swap, TEST_126) {
  s21::stack<int> s21_stack_int{1, 2, 3, 4, 5};
  s21::stack<int> s21_stack_res_int{10, 20};
  s21_stack_int.swap(s21_stack_res_int);
  EXPECT_EQ(s21_stack_int.size(), 2);
  EXPECT_EQ(s21_stack_int.top(), 20);
  EXPECT_EQ(s21_stack_res_int.size(), 5);
  EXPECT_EQ(s21_stack_res_int.top(), 5);
}
TEST(queue, TEST_127) {
  s21::queue<int> s21_queue;

  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.push(3);
  s21_queue.push(4);

  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
}

TEST(queue, TEST_128) {
  s21::queue<int> s21_queue;

  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.push(3);
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.push(3);
  s21_queue.pop();
  s21_queue.pop();
  EXPECT_EQ(s21_queue.front(), 3);
  EXPECT_EQ(s21_queue.back(), 3);
}

TEST(queue_empty, TEST_129) {
  s21::queue<int> s21_queue;
  EXPECT_EQ(s21_queue.empty(), true);
}

TEST(queue_swap, TEST_130) {
  s21::queue<int> s21_queue_one{1, 2, 3, 4, 5, 6};
  s21::queue<int> s21_queue_two{10, 20};
  s21_queue_one.swap(s21_queue_two);

  EXPECT_EQ(s21_queue_one.front(), 10);
  EXPECT_EQ(s21_queue_two.front(), 1);
}

TEST(queue_init_list, TEST_130) {
  s21::queue<int> s21_queue{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_queue.front(), 1);
}

TEST(queue_size, TEST_131) {
  s21::queue<int> s21_queue;
  s21_queue.push(1);
  s21_queue.push(2);
  s21_queue.push(3);
  s21_queue.push(4);
  s21_queue.push(5);
  s21_queue.push(6);
  EXPECT_EQ(s21_queue.size(), 6);
}

TEST(queue_construct, TEST_131) {
  s21::queue<int> s21_list_int;
  EXPECT_EQ(s21_list_int.size(), 0);
}

TEST(queue_construct_two, TEST_132) {
  s21::list<int> s21_list_int(5);
  EXPECT_EQ(s21_list_int.size(), 5);
}

TEST(queue_construct_two, TEST_133) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  EXPECT_EQ(s21_list_int.size(), 4);
  EXPECT_EQ(s21_list_int.front(), 1);
}

TEST(queue_construct_copy, TEST_134) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  s21::queue<int> s21_list_res_int(s21_list_int);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(queue_copy_operator, TEST_135) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  s21::queue<int> s21_list_res_int = s21_list_int;

  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(queue_copy_operator_zero, TEST_136) {
  s21::queue<int> s21_list_int;
  s21::queue<int> s21_list_res_int = s21_list_int;

  EXPECT_EQ(s21_list_res_int.size(), 0U);
}

TEST(queue_operator_move, TEST_137) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  s21::queue<int> s21_list_res_int = std::move(s21_list_int);

  EXPECT_EQ(s21_list_int.size(), 0);
  EXPECT_EQ(s21_list_res_int.size(), 4);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(queue_construct_move, TEST_138) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  s21::queue<int> s21_list_res_int;
  s21_list_res_int = std::move(s21_list_int);

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
}

TEST(queue_move, TEST_139) {
  s21::queue<int> a{43, 43, 43, 5};
  s21::queue<int> b{1};
  a = std::move(b);
  EXPECT_EQ(a.back(), 1);
}
TEST(stack_copy_operator, TEST_140) {
  s21::stack<int> s21_list_int{1, 2, 3, 4};
  s21::stack<int> s21_list_res_int;
  s21_list_res_int = s21_list_int;
  EXPECT_EQ(s21_list_res_int.size(), 4U);
}

TEST(queue_copy_operator, TEST_140) {
  s21::queue<int> s21_list_int{1, 2, 3, 4};
  s21::queue<int> s21_list_res_int;
  s21_list_res_int = s21_list_int;
  EXPECT_EQ(s21_list_res_int.size(), 4U);
}

// TEST(list_const_iterator_arrow, TEST_141) {
//   const s21::list<std::string> s21_list{"a", "b", "c"};
//   auto iter = s21_list.begin();
//
//   EXPECT_EQ(iter->capacity(), 15);
// }

TEST(list_const_iterator, TEST_142) {
  const s21::list<std::string> s21_list{"a", "b", "c"};
  const s21::list<std::string> s21_list_two{"a", "b", "c"};
  auto iter = ++s21_list.begin();
  auto iter_two = s21_list_two.begin();
  EXPECT_EQ(*(iter), "b");
  --iter;
  EXPECT_EQ(*(iter), "a");
  EXPECT_EQ(*(iter++), "a");
  EXPECT_EQ(*(iter--), "b");
  EXPECT_TRUE(*(iter) == *(iter_two));
}

TEST(list_iterator, TEST_143) {
  s21::list<std::string> s21_list{"a", "b", "c"};
  s21::list<std::string> s21_list_two{"a", "b", "c"};
  auto iter = ++s21_list.begin();
  auto iter_two = s21_list_two.begin();
  EXPECT_EQ(*(iter), "b");
  --iter;
  EXPECT_EQ(*(iter), "a");
  EXPECT_EQ(*(iter++), "a");
  EXPECT_EQ(*(iter--), "b");
  EXPECT_TRUE(*(iter) == *(iter_two));
}

// TEST(list_iterator_arrow, TEST_144) {
//   s21::list<std::string> s21_list{"a", "b", "c"};
//   auto iter = s21_list.begin();
//
//   EXPECT_EQ(iter->capacity(), 15);
// }

TEST(list_clear, TEST_145) {
  s21::list<std::string> s21_list{"a", "b", "c"};
  s21_list.clear();

  EXPECT_EQ(s21_list.size(), 0);
}

class SetTest {
 public:
  s21::set<int> empty_set;
  s21::set<int> set_int{3, 5, 7, 2, 1, 1, 4, 6, 0, -5, -1, -10, -12};
  s21::set<std::string> set_string{"baka", "obon", "kokoro"};
  s21::set<double> set_double{1.2, 2.0, 3.345, -1.233};

  std::set<int> empty_set_orig;
  std::set<int> set_int_orig{3, 5, 7, 2, 1, 1, 4, 6, 0, -5, -1, -10, -12};
  std::set<std::string> set_string_orig{"baka", "obon", "kokoro"};
  std::set<double> set_double_orig{1.2, 2.0, 3.345, -1.233};

  s21::set<int> swapped{100, 101, 102};
  std::set<int> swapped_orig{100, 101, 102};
};

TEST(set, Constructor) {
  SetTest tmp;
  EXPECT_EQ(tmp.empty_set.begin() == tmp.empty_set.end(), true);
  EXPECT_EQ(tmp.empty_set_orig.begin() == tmp.empty_set_orig.end(), true);
}

TEST(set, ConstructorList) {
  SetTest tmp;
  int eq[12]{-12, -10, -5, -1, 0, 1, 2, 3, 4, 5, 6, 7};
  int* pos = eq;
  for (auto it : tmp.set_int) {
    EXPECT_EQ(it == *(pos++), true);
  }
}

TEST(set, ConstructorCopy) {
  SetTest tmp;
  s21::set<double> two(tmp.set_double);
  double eq[4]{-1.233, 1.2, 2.0, 3.345};
  double* pos = eq;
  for (auto it : two) {
    EXPECT_EQ(it == *(pos++), true);
  }
  tmp.set_double.clear();
  EXPECT_TRUE(tmp.set_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(set, ConstructorMove) {
  SetTest tmp;
  s21::set<double> two{std::move(tmp.set_double)};
  double eq[4]{-1.233, 1.2, 2.0, 3.345};
  double* pos = eq;
  for (auto it : two) {
    EXPECT_EQ(it == *(pos++), true);
  }
  EXPECT_TRUE(tmp.set_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(set, CopyAssignmentOperator) {
  s21::set<int> originalSet{5, 10, 1, 7};
  s21::set<int> assignedSet;

  assignedSet = originalSet;

  EXPECT_EQ(assignedSet.size(), 4);
  EXPECT_EQ(*assignedSet.begin(), *originalSet.begin());
}

TEST(set, MoveAssignmentOperator) {
  s21::set<int> originalSet{1, 10, 5, 7};
  s21::set<int> movedSet;

  movedSet = std::move(originalSet);

  EXPECT_EQ(movedSet.size(), 4);
  EXPECT_TRUE(originalSet.empty());
}

TEST(set, OperatorsPlusTest) {
  SetTest tmp;
  s21::set<int>::iterator it(tmp.set_int.begin());
  EXPECT_EQ(*(it), -12);
  EXPECT_EQ(*(++it), -10);
}

TEST(set, OperatorsMinusTest) {
  SetTest tmp;
  s21::set<int>::iterator it(tmp.set_int.find(7));
  EXPECT_EQ(*(it), 7);
  EXPECT_EQ(*(--it), 6);
  s21::set<int>::iterator it2 = --(tmp.set_int.end());
  EXPECT_EQ(*(it2), 7);
  EXPECT_EQ(*(--it2), 6);
  EXPECT_EQ(*(--it2), 5);
  EXPECT_EQ(*(--it2), 4);
  EXPECT_EQ(*(--it2), 3);
  EXPECT_EQ(*(--it2), 2);
  EXPECT_EQ(*(--it2), 1);
}

TEST(set, EmptyTest) {
  SetTest tmp;
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
  EXPECT_TRUE(tmp.empty_set.empty() == tmp.empty_set_orig.empty());
  EXPECT_TRUE(tmp.set_string.empty() == tmp.set_string_orig.empty());
  EXPECT_TRUE(tmp.set_double.empty() == tmp.set_double_orig.empty());
}

TEST(set, SizeTest) {
  SetTest tmp;
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  EXPECT_TRUE(tmp.empty_set.size() == tmp.empty_set_orig.size());
  EXPECT_TRUE(tmp.set_string.size() == tmp.set_string_orig.size());
  EXPECT_TRUE(tmp.set_double.size() == tmp.set_double_orig.size());
}

TEST(set, MaxSizeTest) {
  SetTest tmp;
  EXPECT_EQ(tmp.empty_set.max_size(), tmp.set_int.max_size());
}

TEST(set, ClearTest) {
  SetTest tmp;
  tmp.set_int.clear();
  tmp.set_int_orig.clear();
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
}

TEST(set, InsertTest) {
  SetTest tmp;
  tmp.empty_set.insert(1);
  tmp.empty_set.insert(1);
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
  EXPECT_TRUE(*(tmp.set_int.find(1)) == *(tmp.set_int_orig.find(1)));
  EXPECT_EQ(tmp.set_int.find(2) == tmp.set_int.end(),
            tmp.set_int_orig.find(2) == tmp.set_int_orig.end());
}

TEST(set, EraseTest) {
  SetTest tmp;
  tmp.set_int.erase(tmp.set_int.find(5));
  tmp.set_int_orig.erase(5);
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  EXPECT_EQ(tmp.set_int.find(5) == tmp.set_int.end(),
            tmp.set_int_orig.find(5) == tmp.set_int_orig.end());
}

TEST(set, SwapTest) {
  SetTest tmp;
  tmp.set_int.swap(tmp.swapped);
  tmp.set_int_orig.swap(tmp.swapped_orig);
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  auto it_orig = tmp.set_int_orig.begin();
  for (auto it = tmp.set_int.begin(); it != tmp.set_int.end(); ++it) {
    EXPECT_TRUE(*it == *(it_orig++));
  }
}

TEST(set, FindTest) {
  SetTest tmp;
  for (int i = 1; i < 8; ++i) {
    EXPECT_TRUE(tmp.set_int.find(i) != tmp.set_int.end());
    EXPECT_TRUE(tmp.set_int.find(i + 10) == tmp.set_int.end());
  }
}

TEST(set, ContainsTest) {
  SetTest tmp;
  for (int i = 1; i < 8; ++i) {
    EXPECT_TRUE(tmp.set_int.contains(i));
    EXPECT_FALSE(tmp.set_int.contains(i + 10));
  }
}

TEST(set, Merge_set) {
  s21::set<int> set1{-4, 8, 135};
  s21::set<int> set2{1, 3, 6, 7};
  set1.merge(set2);
  EXPECT_TRUE(set1.contains(-4));
  EXPECT_TRUE(set1.contains(8));
  EXPECT_TRUE(set1.contains(135));
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(6));
  EXPECT_TRUE(set1.contains(7));
}

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.size(), orig_map.size());
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = std::move(my_map);
  std::map<int, int> orig_map_copy = std::move(orig_map);
  EXPECT_EQ(my_map.size(), orig_map.size());
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, CopyAssignmentOperator) {
  s21::map<int, char> originalMap{{5, 'a'}, {10, 'b'}, {1, 'a'}, {7, 'f'}};
  s21::map<int, char> assignedMap;

  assignedMap = originalMap;

  EXPECT_EQ(assignedMap.size(), 4);
  EXPECT_EQ((*assignedMap.begin()).first, (*originalMap.begin()).first);
  EXPECT_EQ((*assignedMap.begin()).second, (*originalMap.begin()).second);
}

TEST(map, MoveAssignmentOperator) {
  s21::map<int, char> originalMap{{5, 'a'}, {10, 'b'}, {1, 'a'}, {7, 'f'}};
  s21::map<int, char> movedMap;

  movedMap = std::move(originalMap);

  EXPECT_EQ(movedMap.size(), 4);
  EXPECT_TRUE(originalMap.empty());
}

TEST(map, MapOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map['a'] = "Alisa";
  orig_map['a'] = "Alisa";
  orig_map['b'] = "Ben";
  auto x = my_map['s'];
  EXPECT_EQ(x, "");
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(my_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map.at('a') = "Alisa";
  orig_map.at('a') = "Alisa";
  orig_map.at('b') = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> my_map;
  s21::map<char, std::string> my_map2;
  EXPECT_EQ(my_map.max_size(), my_map2.max_size());
}

TEST(map, MapClear) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(std::make_pair(1, 'a'));
  my_map.insert(std::make_pair(2, 'a'));
  my_map.insert(std::make_pair(3, 'a'));
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(std::make_pair(1, 'a'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(1, 'a');
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
  my_map.insert_or_assign(4, 's');
  EXPECT_TRUE(my_map.contains(4));
}

TEST(map, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.erase(my_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2);
  EXPECT_EQ(my_swap_map.size(), 1);
  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> my_map_added = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_added = {{3, 3}, {4, 4}};

  my_map.merge(my_map_added);
  orig_map.merge(orig_map_added);

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  EXPECT_FALSE(my_map_added.contains(4));
  EXPECT_FALSE(my_map_added.contains(3));
  EXPECT_TRUE(my_map.contains(4));
  EXPECT_TRUE(my_map.contains(3));
}

TEST(multiset, DefaultConstructor) {
  s21::multiset<int> defaultSet;

  EXPECT_EQ(defaultSet.size(), 0);
}

TEST(multiset, RangeConstructor) {
  s21::multiset<int> rangeSet{5, 10, 5, 7};
  EXPECT_EQ(rangeSet.size(), 4);
  EXPECT_EQ(rangeSet.count(5), 2);
  EXPECT_EQ(rangeSet.count(10), 1);
  EXPECT_EQ(rangeSet.count(7), 1);
}

TEST(multiset, CopyConstructor) {
  s21::multiset<int> originalSet{5, 10, 5, 7};
  s21::multiset<int> copySet(originalSet);

  EXPECT_EQ(copySet.size(), 4);
  EXPECT_EQ(*originalSet.begin(), *copySet.begin());
}

TEST(multiset, MoveConstructor) {
  s21::multiset<int> originalSet{5, 10, 5, 7};
  s21::multiset<int> movedSet(std::move(originalSet));

  EXPECT_EQ(movedSet.size(), 4);
  EXPECT_TRUE(originalSet.empty());
}

TEST(multiset, CopyAssignmentOperator) {
  s21::multiset<int> originalSet{5, 10, 5, 7};
  s21::multiset<int> assignedSet;

  assignedSet = originalSet;

  EXPECT_EQ(assignedSet.size(), 4);
  EXPECT_EQ(*assignedSet.begin(), *originalSet.begin());
}

TEST(multiset, MoveAssignmentOperator) {
  s21::multiset<int> originalSet{5, 10, 5, 7};
  s21::multiset<int> movedSet;

  movedSet = std::move(originalSet);

  EXPECT_EQ(movedSet.size(), 4);
  EXPECT_TRUE(originalSet.empty());
}

TEST(multiset, EmptyMethodOnEmptySet) {
  s21::multiset<int> emptySet;

  EXPECT_TRUE(emptySet.empty());
}

TEST(multiset, EmptyMethodOnNonEmptySet) {
  s21::multiset<int> nonEmptySet{5, 10, 5, 7};

  EXPECT_FALSE(nonEmptySet.empty());
}

TEST(multiset, InsertReturnValue) {
  s21::multiset<int> testSet;

  auto it1 = testSet.insert(5);
  EXPECT_EQ(*it1, 5);

  auto it2 = testSet.insert(10);
  EXPECT_EQ(*it2, 10);

  auto it3 = testSet.insert(5);
  EXPECT_EQ(*it3, 5);

  EXPECT_EQ(testSet.size(), 3);
}

TEST(multiset, EraseMethod) {
  s21::multiset<int> testSet{5, 10, 5, 7};

  auto it = testSet.begin();
  ++it;

  testSet.erase(it);

  EXPECT_EQ(testSet.size(), 3);
  EXPECT_EQ(testSet.count(10), 1);
}

TEST(multiset, SwapMethod) {
  s21::multiset<int> set1{5, 10, 5, 7};
  s21::multiset<int> set2{3, 8, 3};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), 3);
  EXPECT_EQ(set1.count(3), 2);
  EXPECT_EQ(set1.count(8), 1);

  EXPECT_EQ(set2.size(), 4);
  EXPECT_EQ(set2.count(5), 2);
  EXPECT_EQ(set2.count(7), 1);
  EXPECT_EQ(set2.count(10), 1);
}

TEST(multiset, MergeMethod) {
  s21::multiset<int> set1{5, 10, 5, 7};
  s21::multiset<int> set2{3, 8, 3};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 7);
  EXPECT_EQ(set1.count(3), 2);
  EXPECT_EQ(set1.count(5), 2);
  EXPECT_EQ(set1.count(7), 1);
  EXPECT_EQ(set1.count(8), 1);
  EXPECT_EQ(set1.count(10), 1);

  EXPECT_EQ(set2.size(), 0);
}

TEST(multiset, FindMethod) {
  s21::multiset<int> testSet{5, 10, 5, 7};

  auto it1 = testSet.find(5);
  EXPECT_EQ(*it1, 5);

  auto it2 = testSet.find(10);
  EXPECT_EQ(*it2, 10);

  auto it3 = testSet.find(15);
  EXPECT_EQ(it3, testSet.end());
}

TEST(multiset, ContainsMethod) {
  s21::multiset<int> testSet{5, 10, 5, 7};

  EXPECT_TRUE(testSet.contains(5));
  EXPECT_TRUE(testSet.contains(10));
  EXPECT_FALSE(testSet.contains(15));
}

TEST(multiset, EqualRangeMethod) {
  s21::multiset<int> testSet{5, 5, 15, 5, 25};

  auto [it1, it2] = testSet.equal_range(15);
  EXPECT_EQ(*it1, 15);
  EXPECT_EQ(*it2, 25);

  auto [it3, it4] = testSet.equal_range(5);
  EXPECT_EQ(*it3, 5);
  EXPECT_EQ(*(++it3), 5);
  EXPECT_EQ(*(++it3), 5);
  EXPECT_EQ(++it3, it4);
  EXPECT_EQ(*it4, 15);
}

TEST(multiset, LowerBoundMethod) {
  s21::multiset<int> testSet{5, 10, 15, 20, 25};

  auto it1 = testSet.lower_bound(10);
  EXPECT_EQ(*it1, 10);

  auto it2 = testSet.lower_bound(17);
  EXPECT_EQ(*it2, 20);

  auto it3 = testSet.lower_bound(30);
  EXPECT_TRUE(it3 == testSet.end());
}

TEST(multiset, UpperBoundMethod) {
  s21::multiset<int> testSet{5, 10, 15, 20, 25};

  auto it1 = testSet.upper_bound(10);
  EXPECT_EQ(*it1, 15);

  auto it2 = testSet.upper_bound(17);
  EXPECT_EQ(*it2, 20);

  auto it3 = testSet.upper_bound(25);
  EXPECT_EQ(it3, testSet.end());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
