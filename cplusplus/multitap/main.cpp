/*
PROVIDED FILE
*/

#include <iostream>
#include <fstream>

using namespace std;

#include "multitap.h"

int main() {

  int size;
  char multitap[512];

  multitap[0] = '\0';

  cout << "====================== Question 1 ======================" << endl << endl;

  size = encode_character('c', multitap);
  cout << "The character 'c' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character('5', multitap);
  cout << "The character '5' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character('Q', multitap);
  cout << "The character 'Q' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character(' ', multitap);
  cout << "The character ' ' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character(',', multitap);
  cout << "The character ',' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  cout << endl;
  multitap[0] = '\0';

  cout << "====================== Question 2 ======================" << endl << endl;

  encode("imperial", multitap);
  cout << "The string 'imperial' encoded in multitap is '" << multitap << "'" << endl;

  encode("cab", multitap);
  cout << "The string 'cab' encoded in multitap is '" << multitap << "'" << endl;

  encode("Meet Anna at 5pm", multitap);
  cout << "The string 'Meet Anna at 5pm' encoded in multitap is '" << multitap << "'" << endl;

  cout << endl;

  return 0;
}
