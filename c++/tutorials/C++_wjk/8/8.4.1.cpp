#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int factorial(int number);

int main() {

  cout << factorial(5) << endl;
  cout << factorial(0) << endl;
  cout << factorial(1) << endl;

  return 0;

}

int factorial(int number) {
  if (number < 0) {
    cout << "Negative number" << endl;
    exit(1);
  }
  else if (number == 0)
    return 1;
  else
    return (number * factorial(number - 1));
}
