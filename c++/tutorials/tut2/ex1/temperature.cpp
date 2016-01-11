#include <iostream>
#include <iomanip>

using namespace std;

int main() {

  const int lower = 0;
  const int upper = 300;
  const int step = 20;
  
  double cels;
  double abs;

  // output the table header
  cout << setiosflags(ios::left);
  cout.width(20);
  cout << "Fahrenheit";
  cout.width(20);
  cout << "Celsius";
  cout.width(20);
  cout << "Absolute" << endl << endl;

  // set the precision and format of the temperature
  cout.setf(ios::fixed);
  cout.precision(2);

  // loop through the F temperatures and compute the C and K temperatures
  for (int i = lower; i <= upper; i += step) {
    cout.width(20);
    cout << i;

    cout.width(20);
    cels = (((float)i - 32) * (5.0 / 9));
    cout << cels;

    cout.width(20);
    abs = cels + 273.15;
    cout << abs << endl;
  }

  return 0;
}
