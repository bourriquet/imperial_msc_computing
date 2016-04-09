/*                                                                                                                                                                                     
   Filename: plugboard.cpp                                                                                                                                                             
   Author: lc3311                                                                                                                                                                      
   Last updated: 09/04/2016                                                                                                                                                            
                                                                                                                                                                                       
   This implementation file contains the function definitions for the Plugboard class                                                                                                  
*/

#include <iostream>
#include <fstream>
#include <string>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"

using namespace std;

/* Constructor function */
Plugboard::Plugboard(const std::string file) {
  check_file(file);
  get_config(file);
};

/* This function checks the plugboard configuration file for any errors and throws exceptions where found */
void Plugboard::check_file(const std::string filename) {
  ifstream in_stream;
  in_stream.open(filename.c_str());

  // check if the file can be opened                                                                                                                                                   
  if (extension(filename) != ".pb" || in_stream.fail()) {
    cerr << "Error opening plugboard configuration file " << filename << ". Exiting..." << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // test each digit in the file                                                                                                                                                       
  int count = 0;
  int test;
  while (!in_stream.eof()) {
    in_stream >> ws;

    // break the loop when the EOF flag is found                                                                                                                                       
    if (in_stream.peek() == EOF)
      break;

    in_stream >> test;

    // if this has failed, then the character is not a number                                                                                                                          
    if (in_stream.fail()) {
      cerr << "Plugboard configuration file " << filename << " contains a non-numeric character " << test << ". Exiting..." << endl;
      throw NON_NUMERIC_CHARACTER;
    }
    // return error code if invalid index found                                                                                                                                        
    if (test < 0 || test >= ALPHABET_SIZE) {
      cerr << "Plugboard configuration file " << filename << " contains a number not in the alphabet " << test << ". Exiting..." << endl;
      throw INVALID_INDEX;
    }
    count++;
  }

  // return error code if the end of the file has been reached and there are too many contacts                                                                                         
  if (count > ALPHABET_SIZE) {
    cerr << "Plugboard configuration file " << filename << " contains too many contacts (" << count << "). Exiting..." << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  // return error code if the end of the file has been reached and there is an incomplete pair                                                                                         
  if (count % 2 == 1) {
    cerr << "Plugboard configuration file " << filename << " contains an incomplete pair of contacts. Exiting..." << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  in_stream.close();

  // get number of contacts                                                                                                                                                            
  number_of_contacts = count;
}

/* This function sets up the configuration of the plugboard */
void Plugboard::get_config(const std::string filename) {
  // create configuration array according to number of contacts                                                                                                                        
  config = new int[number_of_contacts];

  ifstream in_stream;

  // open file                                                                                                                                                                         
  in_stream.open(filename.c_str());

  // populate the configuration array                                                                                                                                                  
  int count = 0;
  while (!in_stream.eof()) {
    in_stream >> ws;

    // break the loop when the EOF flag is found to avoid populating the array with a nonsense number                                                                                  
    if (in_stream.peek() == EOF)
      break;

    // input number to config array                                                                                                                                                    
    in_stream >> config[count];

    // return error code if a double contact is found                                                                                                                                  
    for (int i = 0; i < count; i++) {
      if (config[count] == config[i]) {
        cerr << "Plugboard " << filename << " attempts to create a double contact. " << config[count] << " is paired twice. Exiting..." << endl;
        throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
    count++;
  }
  in_stream.close();
}

/* This function maps the output of a given integer through the plugboard */
int Plugboard::map(int input) {
  // manipulates pairings in configuration array                                                                                                                                       
  for (int i = 0; i < number_of_contacts; i++) {
    if (config[i] == input) {
      if (i % 2 == 0)
        return config[i+1];
      else if (i % 2 == 1)
        return config[i-1];
    }
  }

  // return the input number if no contact                                                                                                                                             
  return input;
}
