#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int count_char(char c);

int main() {

  // output the table header
  cout << setiosflags(ios::left);
  cout.width(20);
  cout << "CHARACTER";
  cout.width(20);
  cout << "OCCURRENCES" << endl << endl;

  // loop through each character and output the number of times each occurs in the file
  for (char c = 'a'; c <= 'z'; c++) {
    cout.width(20);
    cout << c;
    cout.width(20);
    cout << count_char(c) << endl;
  } 

  return 0;
}

// counts how many times c occurs in this file
int count_char(char c) {

  int count = 0;
  char ch;

  // open this file
  ifstream in;
  in.open("charcount.cpp");

  // increment the count if the character == c
  in.get(ch);
  while(!in.eof()) {
    if (ch == c) {
      count++;
    }
    in.get(ch);
  }

  // close the file
  in.close();

  return count;
}
