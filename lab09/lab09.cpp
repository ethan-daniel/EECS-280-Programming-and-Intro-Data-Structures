#include <iostream>
#include <cassert>

#include "lab09.h"

using namespace std;

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses tail recursion
void hailstone(int n) {
  // TASK 1 - YOUR CODE HERE
  assert(n >= 1);
  cout << n << " ";
  if (n == 1){
    return;
  }
  else if (n % 2 == 0) {
    hailstone(n/2);
  }
  else {
    hailstone(n*3 + 1);
  }

}

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses iteration
void hailstone_iter(int n) {
  // TASK 1 - YOUR CODE HERE
  assert(n >= 1);
  while (n != 1){
    cout << n << " ";
    if (n % 2 == 0){
      n/=2;
    }
    else {
      n = n*3 + 1;
    }
  }
  cout << "1";
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses recursion
int count_digits(int n, int digit) {

  return count_digits_tail(n, digit); // TASK 2 - YOUR CODE HERE
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses iteration
int count_digits_iter(int n, int digit) {
  assert(0 <= digit && digit <= 9 && n >= 0);

  int count = 0;

  while(n > 10){
    if (n % 10 == digit){
      ++count;
    }
    n/=10;
  }

  if (n == digit){
    ++count;
  }

  return count; // TASK 2 - YOUR CODE HERE
}

// REQUIRES 0 <= digit <= 9, n >= 0
// EFFECTS: Returns count + the number of times digit appears in n
// NOTE:    Uses tail recursion
static int count_digits_helper(int n, int digit, int count) {
  assert(0 <= digit && digit <= 9 && n >= 0);

  if (n < 10){
    if (n == digit){
      ++count;
    }
    return count;
  }

  else{
    if (n % 10 == digit){
      return count_digits_helper(n/=10, digit, ++count);
    }
    else {
      return count_digits_helper(n/=10, digit, count);
    }
  }

  return count; // TASK 2 - YOUR CODE HERE
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses tail recursion
int count_digits_tail(int n, int digit) {
  assert(0 <= digit && digit <= 9 && n >= 0);

  return count_digits_helper(n, digit, 0);
}
