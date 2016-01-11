#include <iostream>
#include <fstream>

using namespace std;

int main() {

  char character;
  ifstream in;
  int count = 0;

  in.open("ex3.cpp");

  in.get(character);
  while(!in.eof()) {
    count++;
    in.get(character);
  }

  cout << count << endl;

}
