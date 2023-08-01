#include <gtest/gtest.h>

#include <vector>

TEST(VectorConstructor, TRUE) {


}


//TEST(SubMatrix, ExeptionTest) {
//  s21::S21Matrix matrix_one(3, 3);
//  s21::S21Matrix matrix_two(2, 2);
//  EXPECT_ANY_THROW(matrix_one.SubMatrix(matrix_two));
//}




int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
