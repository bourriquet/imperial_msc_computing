#include <iostream>

using namespace std;

void print_backwards();

int main() {
  print_backwards();
  cout << endl;

  return 0;

}

void print_backwards() {
  char character;
  cout << "Enter a character ('.' to end program): ";
  cin >> character;
  
  if (character != '.') {
    print_backwards();
    cout << character;
  }
}
