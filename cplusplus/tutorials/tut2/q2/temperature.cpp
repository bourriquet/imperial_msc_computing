#include <iostream>
#include <iomanip>

using namespace std;

int main() {

  int lower, upper, step;  
  double cels, abs;

  // user input of F values
  cout << "This program gives a table of F, C and K temperatures." << endl;

  cout << "Enter a lower F temp." << endl;
  cin >> lower;

  cout << "Enter an upper F temp." << endl;
  cin >> upper;

  cout << "Enter a step F value." << endl;
  cin >> step;

  //echo input
  cout << "The table of temperatures starting at " << lower << " and ending at $
  cout << " with a step value of " << step << " is as follows..." << endl << en$

  // output table header
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
