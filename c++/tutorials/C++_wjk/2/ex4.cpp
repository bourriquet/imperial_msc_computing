#include <iostream>

using namespace std;

int main() {

  int number;
  int new_num;
  int power;

  cout << "This program raises any number to a positive power." << endl;

  cout << "Enter a number: " << endl;
  cin >> number;

  cout << "Enter a power: " << endl;
  cin >> power;

  new_num = number;
  for (int i = 1; i < power; i++) {
    new_num *= number;
  }

  cout << number << " to the power of " << power << " is " << new_num << endl;

  return 0;

}
