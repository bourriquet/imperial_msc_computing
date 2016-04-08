/*
Tutorial 4, Q 1
*/

#include <iostream>
#include <fstream>

using namespace std;

int main() {

  char character;

  ifstream in;

  // open this file
  in.open("output.cpp");
  in.get(character);

  // while the file hasn't ended...
  while (!in.eof()) {
    cout << character;
    in.get(character);
  }

  // close the file
  in.close();

  cout << endl;

  return 0;

}
