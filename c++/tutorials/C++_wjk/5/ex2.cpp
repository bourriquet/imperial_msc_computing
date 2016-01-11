#include <iostream>

using namespace std;

void print_pyramid(int height);

int main() {

  int h;

  cout << "This program prints a pyramid shape of specified height on the screen." << endl;

  cout << "How high would you like the pyramid?" << endl;
  cin >> h;
  while (h < 1 || h > 30) {
    cout << "Pick another height (must be between 1 and 30)" << endl;
    cin >> h;
  }

  print_pyramid(h);

  return 0;

}

void print_pyramid(int height) {

  for (int i = 1; i <= height; i++) {

    for (int j = 1; j <= (height - i); j++) {
      cout << " ";
    }
    for (int j = 1; j <= (i*2); j++) {
      cout << "*";
    }
    for (int j = 1; j <= (height - i); j++) {
      cout << " ";
    }
    cout << endl;
  }

}
