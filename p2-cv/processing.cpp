// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  // assert(false); // TODO Replace with your implementation!
  // assert(squared_difference(Pixel(), Pixel())); // TODO delete me, this is here to make it compile
  Pixel N, S, W, E;
  int max_energy;

  Matrix_init(energy, img->width, img->height);
  Matrix_fill(energy, 0);

  for (int r = 1, height = Matrix_height(energy); r != height-1; ++r){
    for (int c = 1, width = Matrix_width(energy); c != width-1; ++c){
      N = Image_get_pixel(img, r-1, c);
      S = Image_get_pixel(img, r+1, c);
      W = Image_get_pixel(img, r, c-1);
      E = Image_get_pixel(img, r, c+1);
      *Matrix_at(energy, r, c) = squared_difference(N, S) + squared_difference(W, E);
    }
  }

  max_energy = Matrix_max(energy);
  Matrix_fill_border(energy, max_energy);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  //assert(false); // TODO Replace with your implementation!
  int min_column;
  Matrix_init(cost, energy->width, energy->height);
  Matrix_fill(cost, 0);

  for (int c = 0, width = Matrix_width(cost); c != width; ++c){
    *Matrix_at(cost, 0, c) = *Matrix_at(energy, 0, c);
  }

  for (int r = 1, height = Matrix_height(cost); r != height; ++r){
    for (int c = 0, width = Matrix_width(cost); c != width; ++c){
      if (c == 0){
        min_column = Matrix_column_of_min_value_in_row(cost, r-1, c, c+2);
      }
      else if (c == width-1){
        min_column = Matrix_column_of_min_value_in_row(cost, r-1, c-1, c+1);
      }
      else{
        min_column = Matrix_column_of_min_value_in_row(cost, r-1, c-1, c+2);
      }
      *Matrix_at(cost, r, c) = *Matrix_at(energy, r, c) + *Matrix_at(cost, r-1, min_column);
    }
  }
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  int current = Matrix_column_of_min_value_in_row(cost, Matrix_height(cost)-1, 0, Matrix_width(cost));
  seam[Matrix_height(cost)-1] = current;

  for (int r = Matrix_height(cost)-1; r >= 1; --r){
    if (current == 0){
      seam[r-1] = Matrix_column_of_min_value_in_row(cost, r-1, current, current+2);
    }

    else if (current == Matrix_width(cost)-1){
      seam[r-1] = Matrix_column_of_min_value_in_row(cost, r-1, current-1, current+1);
    }

    else{
      seam[r-1] = Matrix_column_of_min_value_in_row(cost, r-1, current-1, current+2);
    }

    current = seam[r-1];
  }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  assert(Image_width(img) >= 2);
  
  Image* new_img = new Image;
  Image_init(new_img, Image_width(img)-1, Image_height(img));

  int flag = 0; // flipped when seam[r] is passed

  for (int r = 0, height = Image_height(img); r != height; ++r){
    for (int c = 0, width = Image_width(img); c != width; ++c){
      if (c != seam[r] && flag == 0){
        Image_set_pixel(new_img, r, c, Image_get_pixel(img, r, c));
      }
      else if (c != seam[r] && flag == 1){
        Image_set_pixel(new_img, r, c-1, Image_get_pixel(img, r, c));
      }
      else{
        flag = 1;
      }
    }
    flag = 0;
  }

  *img = *new_img;
  delete new_img;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {
  assert(0 < newWidth && newWidth <= Image_width(img)); // TODO Replace with your implementation!

  while(Image_width(img) != newWidth){
    Matrix* energy_m = new Matrix;
    Matrix* cost_m = new Matrix;
    Matrix_init(energy_m, Image_width(img), Image_height(img));
    compute_energy_matrix(img, energy_m);
    compute_vertical_cost_matrix(energy_m, cost_m);

    int *seam = new int[Matrix_height(cost_m)];
    find_minimal_vertical_seam(cost_m, seam);
    remove_vertical_seam(img, seam);

    delete energy_m;
    delete cost_m;
    delete[] seam;
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(0 < newHeight && newHeight <= Image_height(img)); // TODO Replace with your implementation!
  
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(0 < newWidth && newWidth <= Image_width(img));
  assert(0 < newHeight && newHeight <= Image_height(img));

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
