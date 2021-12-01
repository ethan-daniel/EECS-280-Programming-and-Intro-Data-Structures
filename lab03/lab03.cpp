#include <iostream>
#include <fstream>
#include "lab03.h"

using namespace std;

// REQUIRES: str1 and str2 point to C-strings
// EFFECTS:  If str1 and str2 contain exactly the same characters, returns 0.
//           Otherwise, return a positive number if the first differing char
//           has a greater value in str1 than in str2 and a negative number in
//           the opposite case (you may NOT call strcmp).
// NOTE:     You should implement this without using cstring library functions.
int strcmp_eecs280(const char *str1, const char *str2) {

  for (const char *p1 = str1, *p2 = str2;(*p1 != '\0' || *p2 != '\0'); ++p1, ++p2){
    if (*p1 != *p2){
      if (*p1 > *p2){
        return 1;
      }
      else{
        return -1;
      }
    }
  }
  
  return 0;  // TASK 1 - YOUR CODE HERE
}

// EFFECTS:  Prints "Please enter a word: " to prompt the user to enter a word
//           and then reads a word from cin to be returned. After reading the
//           input, clean up by printing a newline to cout.
string get_user_word() {
  string word;
  cout << "Please enter a word: ";
  cin >> word;
  cout << endl;

  return word;
}

// EFFECTS: Opens the given file and returns a vector containing all the words
//          in the file. If the file cannot be opened, prints an error message
//          and returns an empty vector.
vector<string> read_words_from_file(const string &filename) {
  string word;
  vector<string> words;
  ifstream fin(filename);

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    return words;
  }

  while (fin >> word){
    words.push_back(word);
  }

  return words;
}

// EFFECTS:  Returns true if the given word is contained in the vector of valid
//           words.
// NOTE:     You MUST use the strcmp_eecs280 function (NOT strcmp).
//           You should implement this without using cstring library functions.
bool find_word(const char *word, const vector<string> &valid_words) {

  for (int i = 0, size = valid_words.size(); i != size; ++i){
    if (strcmp_eecs280(word, valid_words[i].c_str()) == 0){

      return true;
    }
  }

  return false;
}
