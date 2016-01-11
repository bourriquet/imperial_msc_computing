#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

  cout << setiosflags(ios::left);
  cout.width(20);
  cout << "Number" << "Square Root" << endl << endl;

  cout.setf(ios::fixed);
  cout.precision(2);
  for (int i = 1; i <= 10; i++) {
    cout.width(20);
    cout << i << sqrt((double)i) << endl;
  }

  return 0;
}
