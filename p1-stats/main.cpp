// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
using namespace std;

int main() {

  string filename;
  string column_name;

  cout << "enter a file name" << endl;
  cin >> filename;
  cout << "enter a column name" << endl;
  cin >> column_name;
  cout << "reading column "<< column_name << " from " << filename << endl;

  vector <double> data = extract_column(filename, column_name);
  sort(data);

	cout << "Summary (value: frequency)" << endl;
	for (size_t x = 0; x < summarize(data).size(); x++)
	{
		cout << summarize(data)[x][0] << ": " << summarize(data)[x][1] << endl;
	}
	cout << "\ncount = " << count(data) << endl;
	cout << "sum = " << sum(data) << endl;
	cout << "mean = " << mean(data) << endl;
	cout << "stdev = " << stdev(data) << endl;
	cout << "median = " << median(data) << endl;
	cout << "mode = " << mode(data) << endl;
	cout << "min = " << min(data) << endl;
	cout << "max = " << max(data) << endl;

  std::cout << std::setprecision(1);
	cout << "  0th percentile = " << percentile(data, 0) << endl;
	cout << " 25th percentile = " << percentile(data, 0.25) << endl;
	cout << " 50th percentile = " << percentile(data, 0.5) << endl;
	cout << " 75th percentile = " << percentile(data, 0.75) << endl;
	cout << "100th percentile = " << percentile(data, 1.0) << endl;



}