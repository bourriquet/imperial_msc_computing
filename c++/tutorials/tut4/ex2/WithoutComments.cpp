#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {

  char character;
  char next;

  // flag whether the stream is inside a comment
  bool comment = false;

    cout << "Testing: " << 16/2 << " = " << 4*2 << endl << endl;

    ifstream in;
  ofstream out;

    in.open("comments.cpp");
  out.open("WithoutComments.cpp");

    if (in.fail() || out.fail())
    exit(1);

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

    in.close();
  out.close();

  cout << endl;

  return 0;

}
