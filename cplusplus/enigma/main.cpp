/*                                                                                                                                                                                     
  Filename: main.cpp                                                                                                                                                                   
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This file contains the program to implement the Enigma machine                                                                                                                       
                                                                                                                                                                                       
*/

#include <iostream>
#include <fstream>
#include <string>
#include "enigma.h"
#include "machine.h"
#include "errors.h"

using namespace std;

int main(int argc, char **argv) {

  // minimum number of required files is 3                                                                                                                                             
  if (argc < 3 || argc == 4) {
    cerr << "Insufficient number of component configuration files provided. Exiting..." << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  string message;
  string inp = "";

  Machine *machine;

  try {
    machine = new Machine(argc, argv);
  }
  catch(int error) {
    return error;
  }

  //cout << "Enter a message using capital letters. Press Enter -> Ctrl-D to end the message" << endl;                                                                                 
  cin >> ws;
  while(getline(cin, message)) {
    inp += message;
  }

  for (int i = 0; inp[i] != '\0'; i++) {
    if (!isspace(inp[i])) {
      int input = static_cast<int>(inp[i] - 'A');
      if (input < 0 || input > ALPHABET_SIZE) {
	cerr << "Invalid input character " << inp[i] << ". Input must be a capital letter. Exiting..." << endl;
	return INVALID_INPUT_CHARACTER;
      }
      input = machine->encrypt(input);
      cout << static_cast<char>('A' + input);
    }
  }
  return NO_ERROR;
}
