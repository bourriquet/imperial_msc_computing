/*
PROVIDED FILE
*/

#include <iostream>
#include <fstream>

using namespace std;

#include "braille.h"

int main() {

  int size;
  char braille[512];

  braille[0] = '\0';

  cout << "====================== Question 1 ======================" << endl << endl;

  size = encode_character('t', braille);
  cout << "The character 't' encoded in braille is '" << braille << "' (" << size << " characters)"\
 << endl;

  size = encode_character('Z', braille);
  cout << "The character 'Z' encoded in braille is '" << braille << "' (" << size << " characters)"\
 << endl;

  size = encode_character('5', braille);
  cout << "The character '5' encoded in braille is '" << braille << "' (" << size << " characters)"\
 << endl;

  size = encode_character('.', braille);
  cout << "The character '.' encoded in braille is '" << braille << "' (" << size << " characters)"\
 << endl;

  cout << endl;

  braille[0]='\0';

  cout << "====================== Question 2 ======================" << endl << endl;

  encode("Hello!", braille);
  cout << "The string 'Hello!' encoded in braille is:" << endl << braille << endl << endl;

  encode("S-Club7?", braille);
  cout << "The string 'S-Club7?' encoded in braille is:" << endl << braille << endl;

  cout << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

  print_braille("Hello!", cout);

  cout << endl;

  print_braille("S-Club7?", cout);

  cout << endl;

  return 0;
}
