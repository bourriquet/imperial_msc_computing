#include <iostream>

using namespace std;

int fib(int num);

int main() {

  cout << fib(1) << endl;
  cout << fib(2) << endl;
  cout << fib(3) << endl;
  cout << fib(4) << endl;
  cout << fib(5) << endl;
  cout << fib(6) << endl;

  return 0;

}

int fib(int num) {

  if (num == 1)
    return 1;
  else if (num == 2)
    return 1;
  else if (num > 2) {
    return fib(num - 1) + fib(num - 2);
  }

  return 0;

}
