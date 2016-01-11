#include <iostream>

using namespace std;

int main() {

  int number, new_num, power;

  // user input
  cout << "This program raises any number to a positive power." << endl;

  cout << "Enter a number: " << endl;
  cin >> number;

  cout << "Enter a power: " << endl;
  cin >> power;

  // make a copy of the number
  new_num = number;
  
  // multiply by the original number (power - 1) times
  for (int i = 1; i < power; i++) {
    new_num *= number;
  }
  
  // output the answer
  cout << number << " to the power of " << power << " is " << new_num << endl;

  return 0;

}
