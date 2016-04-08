/*
Tutorial 4, Q 2
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {

  char character;
  ifstream in;
  int count = 0;

  // open this file
  in.open("count.cpp");

  // check if the file opened
  if (in.fail())
    exit(1);

  // loop through every character and increment count
  in.get(character);
  while(!in.eof()) {
    count++;
    in.get(character);
  }

  // close the file
  in.close();

  // output the count
  cout << count << endl;

  return 0;
}
