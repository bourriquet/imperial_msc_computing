/*
Tutorial 4, Q 2

Implementation file
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {

  char character;
  char next;

  // flag whether the stream is inside a comment
  bool comment = false;

  /* Testing */
  cout << "Testing: " << 16/2 << " = " << 4*2 << endl << endl;

  /* Streams */
  ifstream in;
  ofstream out;

  /* Open */
  in.open("comments.cpp");
  out.open("WithoutComments.cpp");

  /* Check that the files have opened correctly */
  if (in.fail() || out.fail())
    exit(1);

  in.get(character);

  /* While the file hasn't ended... */
  while (!in.eof()) {

    /* While not inside a comment and a / is found */
    if (!(comment) && (character == '/')) {
      /* check to see if the next character is a * */ 
      in.get(next);
      /* we are inside a comment */
      if (next == '*') {
        comment = true;
      }
      /* if not, put it back */
      else {
        in.putback(next);
      }
    }
    /* While inside a comment and a * is found */
    if (comment && (character == '*')) {
      /* check to see if the next character is a / */
      in.get(character);
      /* comment has finished */
      if (character == '/') {
        comment = false;
        in.get(character);
      }
    }
    /* else, not in a comment, so output */
    else if (!comment) {
      cout << character;
      out.put(character);
    }
    in.get(character);
  }

  /* Close the streams */
  in.close();
  out.close();

  cout << endl;

  return 0;

}

