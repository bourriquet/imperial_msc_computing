#include <iostream>
#include <fstream>

using namespace std;

int main() {

  ifstream in, in2;
  int count = 0;
  char character;

  // open this file
  in.open("backwards.cpp");

  // loop through every character and increment the count
  in.get(character);
  while (!in.eof()) {
    count++;
    in.get(character);
  }

  // close the file
  in.close();

  // for every character, open the file again, find the character and output it
  for (int n = count; n >= 0; n--) {
    char good;

    in2.open("backwards.cpp");
    in2.get(good);

    for (int i = 0; i < n; i++) {
      in2.get(good);
    }

    cout << good;

    in2.close();
  }

  cout << endl;

  return 0;
}
