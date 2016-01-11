#include <iostream>

using namespace std;

int main() {

  char character;
  int number;

  cout << "Enter a single character." << endl;
  cin >> character;

  number = character;

  if (number >= 65 && number <= 90) {
    cout << character << " in lower case is " << (char)(character + 32) << endl;
  }
  else if (number >= 97 && number <= 122) {
    cout << character << " in upper case is " << (char)(character - 32) << endl;
  }
  else {
    cout << "Invalid character" << endl;
  }

  return 0;
}
