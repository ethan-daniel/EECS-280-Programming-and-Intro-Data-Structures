// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include <cassert>
#include <vector>

#include <numeric>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
  assert(false);
}

int count(vector<double> v) {
  int count = 0;
  for (size_t i = 0; i != v.size(); ++i){
    count += 1;
  }
  return v.size();
}

double sum(vector<double> v) {
  double sum_of_elements = 0.0;
  for (size_t i = 0; i != v.size(); ++i){
    sum_of_elements += v[i];
  }

  const double multiplier = std::pow(10.0, 2);

  return std::ceil(sum_of_elements * multiplier) / multiplier;
}

double mean(vector<double> v) {
  double sum_of_elements = sum(v);
  double count_elements = count(v);

  return (sum_of_elements / count_elements);
}

double median(vector<double> v) {
  int mid = count(v)/2;

  if (mid%2 == 0){
    return (v[mid-1] + v[mid])/2;
  }

  return v[mid];
}

double mode(vector<double> v) {
  assert(false);
}

double min(vector<double> v) {
  assert(false);
}

double max(vector<double> v) {
  assert(false);
}

double stdev(vector<double> v) {
  assert(false);
}

double percentile(vector<double> v, double p) {
  assert(false);
}