// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include <cassert>
#include <vector>

#include "p1_library.h"
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
  vector<vector<double>> pair_list;
  vector<double> pair;
  int count = 1;
  
  sort(v);
  for (size_t i = 0; i != v.size(); ++i){
    if (v[i] != v[i + 1]){
      pair.push_back(v[i]);
      pair.push_back(count);
      pair_list.push_back(pair);

      pair.empty();
      count = 1;
    }
    else{
      ++count;
    }
  }

  return pair_list;
}

int count(vector<double> v) {

  return v.size();
}

double sum(vector<double> v) {
  double sum_of_elements = 0.0;
  for (size_t i = 0; i != v.size(); ++i){
    sum_of_elements += v[i];
  }

  return sum_of_elements;
}

double mean(vector<double> v) {
  double sum_of_elements = sum(v);
  double count_elements = count(v);

  return (sum_of_elements / count_elements);
}

double median(vector<double> v) {
  int v_size = count(v);
  int mid = v_size/2;

  if (v_size%2 == 0){
    return (v[mid-1] + v[mid])/2;
  }

  return v[mid];
}

double mode(vector<double> v) {

  if (v.size() == 1){
    return v[0];
  }

  sort(v);
  double most_common_number = 0.0;
  int most_common_count = 0;
  int count = 1;
  for (size_t i = 0; i != v.size(); ++i){
    if (v[i] != v[i + 1]){
      if (count > most_common_count){
        most_common_count = count;
        most_common_number = v[i];
      }
      count = 1;
    }
    else{
      ++count;
    }
  }

  return most_common_number;
}

double min(vector<double> v) {
  sort(v);

  return v[0];
}

double max(vector<double> v) {
  sort(v);

  return v.back();
}

double stdev(vector<double> v) {
  double N = count(v);
  double v_mean = mean(v);
  double a = 0.0;

  for (size_t i = 0; i != N; ++i){
    a += pow((v[i] - v_mean), 2);
  }

  a = sqrt(a/(N-1));

  return a;

}

double percentile(vector<double> v, double p) {
  sort(v);
  double N = (p/100) * (count(v) - 1) + 1;
  double fractpart = 0;
  double intpart = 0;
  
  fractpart = modf(N, &intpart);

  double x = v[intpart - 1];
  double y = median(v);

  double ans = x + fractpart * (y - x);

  return ans;

}