#include <iostream>
#include <fstream>

using namespace std;

int main() {

  char character;
  char next;
  bool comment = false;

  /* Testing */
  cout << "Testing: " << 16/2 << " = " << 4*2 << endl << endl;


  /* Streams */
  ifstream in;
  ofstream out;

  /* Open */
  in.open("ex2.cpp");
  out.open("WithoutComments.cpp");

  in.get(character);
  while (!in.eof()) {
    if (!(comment) && (character == '/')) {
      in.get(next);
      if (next == '*') {
	comment = true;
      }
      else {
	in.putback(next);
      }
    }
    if (comment && (character == '*')) {
      in.get(character);
      if (character == '/') {
	comment = false;
	in.get(character);
      }
    }
    else if (!comment) {
      cout << character;
      out.put(character);
    }
    in.get(character);
  }
  cout << endl;
  in.close();
  out.close();

  return 0;

}
