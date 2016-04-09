/*                                                                                                                                                                                     
  Filename: rotor.cpp                                                                                                                                                                  
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This implementation file contains the function declarations for the Rotor class                                                                                                      
*/

#include <iostream>
#include <fstream>
#include "enigma.h"
#include "rotor.h"
#include "errors.h"

using namespace std;

/* Constructor function */
Rotor::Rotor(const std::string filename, const int starting_pos) {
  current_position = starting_pos;
  check_file(filename);
  get_initial_config(filename);
};

/* This function checks the rotor configuration file */
void Rotor::check_file(const std::string filename) {
  ifstream in_stream;

  // open file                                                                                                                                                                         
  in_stream.open(filename.c_str());

  // if this has failed, there is an error opening the file                                                                                                                            
  if (extension(filename)!= ".rot" || in_stream.fail()) {
    cerr << "Error opening rotor configuration file " << filename << ". Exiting..." << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // test each digit in the file                                                                                                                                                       
  int test;
  int count = 0;
  while (!in_stream.eof()) {
    in_stream >> ws;

    // break the loop when the EOF is found to avoid populating the array with a nonsense number                                                                                       
    if (in_stream.peek() == EOF)
      break;

    in_stream >> test;

    // if this has failed, then a non-integer has been found                                                                                                                           
    if (in_stream.fail()) {
      cerr << "Rotor configuration file " << filename << " contains a non-numeric character " << test << ". Exiting..." << endl;
      throw NON_NUMERIC_CHARACTER;
    }
    
    // return error code if invalid index found                                                                                                                                        
    if (test < 0 || test >= ALPHABET_SIZE) {
      cerr << "Rotor configuration file " << filename << " contains a number not in the alphabet " << test << ". Exiting..." << endl;
      throw INVALID_INDEX;
    }
    count++;
  }
  // return error code if not enough rotor contacts / not at least one notch                                                                                                           
  if (count < (ALPHABET_SIZE + 1)) {
    cerr << "Rotor " << filename << " does not contain enough contacts/notches. Exiting..." << endl;
    throw INVALID_ROTOR_MAPPING;
  }

  // get number of notches                                                                                                                                                             
  number_of_notches = count - ALPHABET_SIZE;

  in_stream.close();
}

/* This function sets up the initial configuration of the reflector */
void Rotor::get_initial_config(const std::string filename) {
  notches = new int[number_of_notches];
  ifstream in_stream;

  // open file                                                                                                                                                                         
  in_stream.open(filename.c_str());

  // populate the configuration array                                                                                                                                                  
  int count = 0;
  while (!in_stream.eof()) {
    in_stream >> ws;

    // break the loop when the EOF is found to avoid populating the array with a nonsense number                                                                                       
    if (in_stream.peek() == EOF)
      break;

    // rotor contacts                                                                                                                                                                  
    if (count < ALPHABET_SIZE) {
      in_stream >> config[count];

      // return error code if a double contact found                                                                                                                                   
      for (int i = 0; i < count; i++) {
        if (config[count] == config[i]) {
          cerr << "Rotor " << filename << " attempts to create a double contact. " << config[count] << " is paired twice. Exiting..." << endl;
          throw INVALID_ROTOR_MAPPING;
        }
      }
    }
    
    // notches                                                                                                                                                                         
    else if (count >= ALPHABET_SIZE && count < number_of_notches + ALPHABET_SIZE) {
      in_stream >> notches[count-ALPHABET_SIZE];

      // return error code if a double notch contact found                                                                                                                             
      for (int i = 0; i < count-ALPHABET_SIZE; i++) {
        if (notches[count-ALPHABET_SIZE] == notches[i]) {
          cerr << "Rotor " << filename << " attempts to create a double notch. " << config[count-ALPHABET_SIZE] << " is already a notch. Exiting..." << endl;
          throw INVALID_ROTOR_MAPPING;
        }
      }
    }
    count++;
  }
  in_stream.close();
}

/* This function shifts the rotor up one position */
void Rotor::shift_up() {
  current_position++;
  remainder(current_position);
}

/* This function maps the input integer forwards through the rotor */
int Rotor::map_forwards(int input) {
  input += get_current_position();
  remainder(input);
  input = config[input];
  input -= get_current_position();
  remainder(input);
  return input;
}

/* This function maps the input integer backwards through the rotor */
int Rotor::map_backwards(int input) {
  input += get_current_position();
  remainder(input);

  int position;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (config[i] == input)
      position = i;
  }
  remainder(position);
  position -= get_current_position();
  remainder(position);
  return position;
}

/* This function returns true if the rotor to the left needs to be shifted */
bool Rotor::shift_left() {
  for (int i = 0; i < number_of_notches; i++) {
     if (notches[i] == current_position)
      return true;
  }
  return false;
}

/* This function gets the current position of the rotor (as it is private) */
int Rotor::get_current_position() {
  return current_position;

}
