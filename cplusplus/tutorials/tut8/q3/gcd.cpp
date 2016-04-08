/*
Tutorial 8, Q 3
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int gcd(int num1, int num2);

int main() {
  int num_1, num_2;

  cout << "This program computes the greatest common divisor of two positive integers" << endl;
  cout << "Enter the first positive integer: " << endl;
  cin >> num_1;
  cout << "Enter the second positive integer: " << endl;
  cin >> num_2;

  cout << gcd(num_1, num_2) << endl;

  return 0;

}

int gcd(int num1, int num2) {

  if (num1 < 1 || num2 < 1) {
    cout << "Numbers must be positive" << endl;
    exit(1);
  } else if (num1 == num2) {
    return num1;
  } else if (num1 < num2) {
    return gcd(num1, (num2-num1));
  } else {
    return gcd(num2, (num1-num2));
  }
}
