#include <iostream>
#include <fstream>

using namespace std;

int main() {

  ifstream in;
  ifstream in2;
  int count = 0;
  char character;

  in.open("ex4.cpp");
  in.get(character);
  while (!in.eof()) {
    count++;
    in.get(character);
  }
  cout << count << endl;
  in.close();


  for (int n = count; n >= 0; n--) {
    char good;

    in2.open("ex4.cpp");
    in2.get(good);

    for (int i = 0; i < n; i++) {
      in2.get(good);
    }
    cout << good;
    in2.close();
  }

  cout << endl;
}
