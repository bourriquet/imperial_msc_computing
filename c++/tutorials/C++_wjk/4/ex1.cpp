#include <iostream>
#include <fstream>

using namespace std;

int main() {

  char character;

  ifstream in;

  in.open("ex1.cpp");
  in.get(character);

  while (!in.eof()) {
    cout << character;
    in.get(character);
  }

  in.close();
  cout << endl;


  return 0;

}
