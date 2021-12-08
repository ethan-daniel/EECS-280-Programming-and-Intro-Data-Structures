// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
  mat->width = width;
  mat->height = height;
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << Matrix_width(mat) << " " << Matrix_height(mat) << std::endl;

  for (int r = 0, height = Matrix_height(mat); r != height; ++r){
    for (int c = 0, width = Matrix_width(mat); c != width; ++c){
      os << *Matrix_at(mat, r, c) << " ";
    }
    os << std::endl;
  }
  
} // PASSES BASIC

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH);
  return mat->width;
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  return mat->height;
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  return ((ptr - &mat->data[0])/Matrix_width(mat));
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  return ((ptr - &mat->data[0])%Matrix_width(mat));
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);

  return (&mat->data[mat->width * row + column]);
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);

  return (&mat->data[mat->width * row + column]);
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for (int r = 0, height = Matrix_height(mat); r != height; ++r){
    for (int c = 0, width = Matrix_width(mat); c != width; ++c){
      *Matrix_at(mat, r, c) = value;
    }
  }
} // PASSES BASIC

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {

  for (int c = 0, width = Matrix_width(mat), height = Matrix_height(mat); 
        c != width; ++c){
    *Matrix_at(mat, 0, c) = value;
    *Matrix_at(mat, height - 1, c) = value;
  } // Highest and lowest rows are filled

  for (int r = 1, height = Matrix_height(mat); r != height-1; ++r){
    for (int c = 0, width = Matrix_width(mat); c != width; ++c){
      if (c == 0 || c == width-1){
        *Matrix_at(mat, r, c) = value;
      }
    }   
  } // Fill leftmost and rightmost elements of the remaining rows
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = *Matrix_at(mat, 0, 0);

  for (int r = 0, height = Matrix_height(mat); r != height; ++r){
    for (int c = 0, width = Matrix_width(mat); c != width; ++c){
      int current = *Matrix_at(mat, r, c);
      if (current > max){
        max = current;
      }
    }   
  }

  return max;
}


// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int min = *Matrix_at(mat, row, column_end-1);
  int min_column = column_end-1;

  for (int c = column_end-1; c >= column_start; --c){
    int current = *Matrix_at(mat, row, c);
    if(current <= min){
      min = current;
      min_column = c;
    }
  }
  
  return min_column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  return *Matrix_at(mat, row, Matrix_column_of_min_value_in_row(mat, row, column_start, column_end));
}
