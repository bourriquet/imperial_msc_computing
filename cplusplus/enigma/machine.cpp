/*                                                                                                                                                                                     
  Filename: machine.cpp                                                                                                                                                                
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This file contains the function definitions for the Machine class                                                                                                                    
*/

#include <iostream>
#include <fstream>
#include "machine.h"
#include "enigma.h"
#include "errors.h"

using namespace std;

/* Constructor function */
Machine::Machine(int argc, char **argv) {
  plugboard = new Plugboard(argv[1]);
  reflector = new Reflector(argv[2]);
  num_rotors = argc - 4;
  if (num_rotors > 0) {
    get_rotor_positions(argv[argc-1]);
    rotors = new Rotor*[num_rotors];
    for (int i = 0; i < num_rotors; i++) {
      rotors[i] = new Rotor(argv[3+i], positions[i]);
    }
  }
};

/* This function gets the starting positions of the rotors */
void Machine::get_rotor_positions(const std::string filename) {
  // create array according to number of rotors                                                                                                                                        
  positions = new int[num_rotors];

  ifstream in_stream;
  in_stream.open(filename.c_str());

  // if this has failed, then there is an error opening the configuration file                                                                                                         
  if (extension(filename)!= ".pos" || in_stream.fail()) {
    cerr << "Error opening rotor position configuration file " << filename << ". Exiting..." << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  int count = 0;

  // populate the rotor positions array                                                                                                                                                
  while (!in_stream.eof()) {
    in_stream >> ws;

    // break the loop if EOF flag found                                                                                                                                                
    if (in_stream.peek() == EOF) {
      break;
    }
    
    in_stream >> positions[count];

    // check if input is an integer                                                                                                                                                    
    if (in_stream.fail()) {
      cerr << "Rotor positions configuration file " << filename << " contains a non-numeric character " << positions[count]<< ". Exiting..." << endl;
      throw NON_NUMERIC_CHARACTER;
    }

    // check if the input is between 0 and 25                                                                                                                                          
    if (positions[count] < 0 || positions[count] >= ALPHABET_SIZE) {
      cerr << "Rotor positions configuration file " << filename << " contains a number not in the alphabet " << positions[count] << ". Exiting..." << endl;
      throw INVALID_INDEX;
    }
    count++;
  }
  // check if enough rotor positions provided                                                                                                                                          
  if (count < num_rotors) {
    cerr << "Not enough starting positions provided for number of rotors (" << num_rotors << ") in " << filename<< ". Exiting..." << endl;
    throw NO_ROTOR_STARTING_POSITION;
  }
  in_stream.close();
}

/* This function encrypts a digit, returning the encrypted digit */
int Machine::encrypt(int input) {
  if (num_rotors > 0)
    shift();

  // map through plugboard                                                                                                                                                             
  input = plugboard->map(input);

  // map through rotors right to left                                                                                                                                                  
  if (num_rotors > 0) {
    for (int i = num_rotors - 1; i >= 0; i--) {
      input = rotors[i]->map_forwards(input);
    }
  }

  // map through reflector                                                                                                                                                             
  input = reflector->map(input);

  // map through rotors left to right                                                                                                                                                  
  if (num_rotors > 0) {
    for (int i = 0; i < num_rotors; i++) {
      input = rotors[i]->map_backwards(input);
    }
  }

  // map through plugboard                                                                                                                                                             
  input = plugboard->map(input);

  return input;

}

void Machine::shift() {

  int i = num_rotors - 1;
  rotors[i]->shift_up();

  while (i > 0 && rotors[i]->shift_left()) {
    i--;
    rotors[i]->shift_up();
  }
}
