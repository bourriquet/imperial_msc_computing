#include <iostream>
#include <cmath>

using namespace std;

bool prime(int num);

int main() {

  int number;

  cout << "This program checks if a number between 1 and 1000 is prime." << endl;

  do {
    cout << "Enter a number between 1 and 1000." << endl;
    cin >> number;
  } while (number < 1 || number > 1000);

  cout << "The number " << number << " is";
  if (!prime(number))
    cout << " not";
  cout << " prime." << endl;

  return 0;
}

bool prime(int num) {

  for (int i = 2; i < num; i++) {
    if ((num % i) == 0) {
      return false;
    }
  }

  return true;
}
