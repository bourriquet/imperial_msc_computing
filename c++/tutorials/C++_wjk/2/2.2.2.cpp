#include <iostream>

using namespace std;

int main() {

  char character;

  for (int number = 32; number <= 126; number++) {
    character = number;

    cout << "The character '" << character << "' is represented as the number ";
    cout << dec << number << " decimal or " << hex << number << " hex." << endl;
  }

  return 0;
}
