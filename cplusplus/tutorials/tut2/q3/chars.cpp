/*
Tutorial 2, Q 3
*/

#include <iostream>

using namespace std;

int main() {

  char character;
  int number;

  // user input
  cout << "Enter a single character." << endl;
  cin >> character;

  // convert character to ASCII
  number = character;

  // convert an upper case character to its lower case equivalent
  if (number >= 65 && number <= 90) {
    cout << character << " in lower case is " << (char)(character + 32) << endl;
  }
  // convert a lower case character to its upper case equivalent
  else if (number >= 97 && number <= 122) {
    cout << character << " in upper case is " << (char)(character - 32) << endl;
  }
  // else, the character isn't valid (in this case)
  else {
    cout << character << " is not a letter" << endl;
  }

  return 0;
}
