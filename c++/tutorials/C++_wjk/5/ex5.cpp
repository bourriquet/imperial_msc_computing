#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int count_char(char c);

int main() {

  cout << setiosflags(ios::left);

  cout.width(20);
  cout << "CHARACTER";
  cout.width(20);
  cout << "OCCURRENCES" << endl << endl;

  for (char c = 'a'; c <= 'z'; c++) {
    cout.width(20);
    cout << c;
    cout.width(20);
    cout << count_char(c) << endl;
  } 

  return 0;

}

int count_char(char c) {

  int count = 0;
  char ch;

  ifstream in;
  in.open("ex5.cpp");

  in.get(ch);
  while(!in.eof()) {
    if (ch == c) {
      count++;
    }
    in.get(ch);
  }
  in.close();
  return count;
}
