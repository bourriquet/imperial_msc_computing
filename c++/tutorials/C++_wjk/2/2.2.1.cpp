#include <iostream>

using namespace std;

int main() {

  int number;
  char character;

  cout << "Type in a character:" << endl;
  cin >> character;

  number = character;

  cout << "The character '" << character << "' is represented as the number ";
  cout << number << " in the computer." << endl;

  return 0;

}
