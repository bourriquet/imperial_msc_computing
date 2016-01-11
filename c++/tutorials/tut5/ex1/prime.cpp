#include <iostream>
#include <cmath>

using namespace std;

bool prime(int num);

int main() {

  int number;

  cout << "This program checks if a number between 1 and 1000 is prime." << endl;

  // get correct user input
  do {
    cout << "Enter a number between 1 and 1000." << endl;
    cin >> number;
  } while (number < 1 || number > 1000);

  // output whether the number is prime
  cout << "The number " << number << " is";
  if (!prime(number))
    cout << " not";
  cout << " prime." << endl;

  return 0;
}

// returns true if the number is prime
bool prime(int num) {

  // if the number is divisible by any number other than 1 or itself, then it isn't prime
  for (int i = 2; i < num; i++) {
    if ((num % i) == 0) {
      return false;
    }
  }

  return true;
}
