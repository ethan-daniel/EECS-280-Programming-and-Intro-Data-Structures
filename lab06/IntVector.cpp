// Completed Task 1 and optional tasks: Task 2 and 3

#include <iostream>
#include <cassert>
#include "IntVector.h"

using namespace std;

// Default constructor.
//EFFECTS: Constructs an empty IntVector.
IntVector::IntVector() : num_elts(0) {assert(check_invariants());}

//REQUIRES: this IntVector is not full
//MODIFIES: this IntVector
//EFFECTS:  Adds value to the end of this IntVector.
void IntVector::push_back(int value) {
  assert(check_invariants());
  assert(!full());
  data[num_elts] = value;
  ++num_elts;
  assert(check_invariants());
}

//REQUIRES: this IntVector is not empty
//MODIFIES: this IntVector
//EFFECTS:  Removes the last element in this IntVector.
void IntVector::pop_back() {
  assert(check_invariants());
  assert(!empty());
  --num_elts;
  assert(check_invariants());
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
int & IntVector::at(int index) {
  assert(check_invariants());
  assert(0 <= index && index < CAPACITY);
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
const int & IntVector::at(int index) const {
  assert(check_invariants());
  assert(0 <= index && index < CAPACITY);
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
int & IntVector::operator[](int index) {
  assert(check_invariants());
  assert(0 <= index && index < CAPACITY);
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
const int & IntVector::operator[](int index) const {
  assert(check_invariants());
  assert(0 <= index && index < CAPACITY);
  return data[index];
}

//EFFECTS:  Returns the number of elements of this IntVector.
int IntVector::size() const {
  assert(check_invariants());
  return num_elts;
}

//EFFECTS:  Returns true if this IntVector is empty, false otherwise.
bool IntVector::empty() const {
  assert(check_invariants());
  if (num_elts == 0){
    return true;
  }
  return false;
}

//EFFECTS:  Returns true if this IntVector is at capacity, false otherwise.
//          That is, you may add elements if and only if full() is false.
bool IntVector::full() const {
  assert(check_invariants());
  if (num_elts == CAPACITY){
    return true;
  }
  return false;
}

//EFFECTS:  Prints to os all elements in this IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
void IntVector::print(ostream &os) const {
  assert(check_invariants());
  os << "[";
  for (int i = 0; i < num_elts; i++) {
    os << " " << data[i];
    if (i < num_elts - 1) {
      os << ",";
    }
  }
  os << " ]";
  assert(check_invariants());
}

//EFFECTS:  Returns true if the representation invariants hold.
//          For IntVector, the only invariants are 0 <= num_elts and
//          num_elts <= CAPACITY.
bool IntVector::check_invariants() const {
  if (0 <= num_elts && num_elts <= CAPACITY){
    return true;
  }
  return false;
}

//EFFECTS:  Prints to os all elements in the IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
ostream & operator<<(ostream & os, const IntVector &v) {
  // TASK 1 - YOUR CODE HERE

  // Always return the stream at end of the insertion operator
  os << "[";
  for (int i = 0, size = v.size(); i < size; i++) {
    os << " " << v[i];
    if (i < size - 1) {
      os << ",";
    }
  }
  os << " ]";

  return os;
}
