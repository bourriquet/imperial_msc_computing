#include <iostream>
#include <cmath>

using namespace std;

int main() {

  float number;

  cout << "Type a real number." << endl;
  cin >> number;
  cout.setf(ios::scientific);
  cout.precision(2);
  cout << "The square root of " << number << " is approx. " << sqrt(number) << endl;

  return 0;

}
