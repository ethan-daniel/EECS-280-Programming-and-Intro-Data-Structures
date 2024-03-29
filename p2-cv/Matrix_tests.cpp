// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

TEST(test_print_basic){
  Matrix *mat = new Matrix;

  ostringstream oss;

  const int value = 9;
  Matrix_init(mat, 3, 2);
  Matrix_fill(mat, value);

  string expected = "3 2\n9 9 9 \n9 9 9 \n";

  Matrix_print(mat, oss);
  ASSERT_EQUAL(oss.str(), expected);

  delete mat;
}

TEST(test_fill_border_basic){
  Matrix *mat = new Matrix;

  ostringstream oss;

  const int value = 9;
  int border_value = 1;
  
  Matrix_init(mat, 5, 4);
  Matrix_fill(mat, value);

  string expected = "5 4\n1 1 1 1 1 \n1 9 9 9 1 \n1 9 9 9 1 \n1 1 1 1 1 \n";

  Matrix_fill_border(mat, border_value);
  Matrix_print(mat, oss);

  ASSERT_EQUAL(oss.str(), expected);

  delete mat;
}

TEST(test_max_basic){
  Matrix *mat = new Matrix;

  const int value = 9, max_value = 500;

  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, value);

  *Matrix_at(mat, 2, 2) = max_value;

  ASSERT_EQUAL(max_value, Matrix_max(mat));

  delete mat;
}

TEST(test_column_of_min_value_in_row_basic){
  Matrix *mat = new Matrix;

  const int value = 9;

  Matrix_init(mat, 6, 6);
  Matrix_fill(mat, value);

  *Matrix_at(mat, 2, 2) = 1;
  *Matrix_at(mat, 2, 3) = 2;
  *Matrix_at(mat, 2, 4) = 3;

  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 0, 6));
  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 1, 6));
  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 2, 6));
  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 0, 5));
  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 0, 4));
  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 2, 0, 3));

  ASSERT_EQUAL(3, Matrix_column_of_min_value_in_row(mat, 2, 3, 6));
  ASSERT_EQUAL(4, Matrix_column_of_min_value_in_row(mat, 2, 4, 6));

  Matrix_fill(mat, value);

  *Matrix_at(mat, 3, 1) = 1;
  *Matrix_at(mat, 3, 2) = 1;
  *Matrix_at(mat, 3, 3) = 1;

  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 0, 6));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 1, 6));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 0, 5));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 0, 4));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 0, 3));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 0, 2));

  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 1, 2));
  ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 3, 1, 3));

  ASSERT_EQUAL(2, Matrix_column_of_min_value_in_row(mat, 3, 2, 6));
  ASSERT_EQUAL(3, Matrix_column_of_min_value_in_row(mat, 3, 3, 6));

  delete mat;
}

TEST(test_min_value_in_row_basic){
  Matrix *mat = new Matrix;

  const int value = 15;

  Matrix_init(mat, 6, 6);
  Matrix_fill(mat, value);

  *Matrix_at(mat, 2, 2) = 7;
  *Matrix_at(mat, 2, 3) = 8;
  *Matrix_at(mat, 2, 4) = 9;

  ASSERT_EQUAL(7, Matrix_min_value_in_row(mat, 2, 0, 6));
  ASSERT_EQUAL(8, Matrix_min_value_in_row(mat, 2, 3, 6));
  ASSERT_EQUAL(9, Matrix_min_value_in_row(mat, 2, 4, 6));

  Matrix_fill(mat, value);

  *Matrix_at(mat, 2, 2) = 1;
  *Matrix_at(mat, 2, 3) = 1;
  *Matrix_at(mat, 2, 4) = 1;

  ASSERT_EQUAL(1, Matrix_min_value_in_row(mat, 2, 0, 6));
  ASSERT_EQUAL(1, Matrix_min_value_in_row(mat, 2, 2, 6));
  ASSERT_EQUAL(1, Matrix_min_value_in_row(mat, 2, 3, 6));

  delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
