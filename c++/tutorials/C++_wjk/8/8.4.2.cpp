#include <iostream>
#include <cstdlib>

using namespace std;

float raise_power(float number, int power);

int main() {

  cout << raise_power(2,5) << endl;

  return 0;

}

float raise_power(float number, int power) {
  
  if (power < 0) {
    cout << "Can't raise to negative power" << endl;
    exit(1);
  }
  else if (power == 0)
    return (1.0);
  else
    return (number * raise_power(number,power-1));
}
