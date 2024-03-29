/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

const double epsilon = 0.001; // precise to 2 decimal points

void test_sum_small_data_set();
void test_count_small_data_set();
void test_mean_data_set();
void test_mean_data_set();
void test_median_data_set();
void test_mode_data_set();
void test_min_data_set();
void test_max_data_set();
void test_stdev_data_set();
void test_percentile_data_set();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  test_count_small_data_set();
  test_mean_data_set();
  test_mean_data_set();
  test_median_data_set();
  test_mode_data_set();
  test_min_data_set();
  test_max_data_set();
  test_stdev_data_set();
  test_percentile_data_set();
  // Call your test functions here

  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "Pass!" << endl;
}

// Add the test function implementations here.

void test_count_small_data_set() {
  cout << "test_count_small_data_set" << endl;

  vector<double> data;
  vector<double> empty;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(count(data) == 3);
  assert(count(empty) == 0); // No REQUIRES clause

  assert(count({-3, -5, 7, 100, -100, 75, -0.75}) == 7);

  cout << "Pass!" << endl;

}

void test_mean_data_set() {
  cout << "test_mean_data_set" << endl;

  vector<double> data = {1, 2, 3};
  vector<double> data2 = {1, 2, 3.6};

  assert(mean(data) == 2);

  //assert(mean(data2) == 2.2);
  assert(abs(mean(data2) - 2.2) < epsilon);

  cout << "Pass!" << endl;
}

void test_median_data_set() { 
  cout << "test_median_data_set" << endl;

  vector<double> data = {1, 3, 3, 6, 7, 8, 9};
  vector<double> data2 = {1, 2, 3, 4, 5, 6, 8, 9};

  assert(median(data) == 6);
  assert(median(data2) == 4.5);
  assert(median({15, 20, 35, 40, 50}) == 35);

  cout << "Pass!" << endl;
}

void test_mode_data_set() {
  cout << "test_mode_data_set" << endl;

  assert(mode({2, 2, 2, 2, 4, 4, 5, 5, 5}) == 2); // sorted
  assert(mode({1, 2, 3, 2, 3, 4, 8, 3}) == 3); // unsorted
  assert(mode({3}) == 3); // single element
  assert(mode({1, 2, 1, 2}) == 1); // a tie
  assert(abs(mode({3.6, 4, 5.6, 7.8, 3.6, 3.6, 90, 3.6, 45, -13, 0, 3.6}) - 3.6) < epsilon); // doubles and ugly vector


//  Example: mode({1,2,3}) = 1
//  Example: mode({1,1,2,2}) = 1
//  Example: mode({2,2,1,1}) = 1
//  Example: mode({1,2,1,2}) = 1
//  Example: mode({1,2,1,2,2}) = 2

  assert(mode({1, 2, 3}) == 1);
  assert(mode({1, 1, 2, 3}) == 1);
  assert(mode({2, 2, 1, 1}) == 1);
  assert(mode({1, 2, 1, 2}) == 1);
  assert(mode({1, 2, 1, 2, 2}) == 2);

  cout << "Pass!" << endl;
}

void test_min_data_set(){
  cout << "test_min_data_set" << endl;

  assert(min({1, 2, 3}) == 1);
  assert(min({-1, 1, 3}) == -1); // negative
  assert(min({4, 4, 4}) == 4); // same element
  assert(min({5, 4, 2, 1, 2, 3}) == 1);

  cout << "Pass!" << endl;
}

void test_max_data_set(){
  cout << "test_max_data_set" << endl;
  
  assert(max({1, 2, 3}) == 3);
  assert(max({-3, -2, -1}) == -1); // negative
  assert(max({4, 4, 4}) == 4); // same element

  cout << "Pass!" << endl;

}

void test_stdev_data_set(){
  cout << "test_stdev_data_set" << endl;

  assert(abs(stdev({10, 8, 10, 8, 8, 4}) - 2.19) < epsilon); // test "corrected" version

  cout << "Pass!" << endl;
}

void test_percentile_data_set(){
  cout << "test_percentile_data_set" << endl;

  assert(abs(percentile({15, 20, 35, 40, 50}, 40) - 29) < epsilon);

  cout << "Pass!" << endl;
}