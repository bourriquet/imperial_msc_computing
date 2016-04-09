/*                                                                                                                                                                                     
  Filename: reflector.cpp                                                                                                                                                              
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This implementation file contains the function definitions for the Reflector class                                                                                                   
*/

#include <iostream>
#include <fstream>
#include "enigma.h"
#include "reflector.h"
#include "errors.h"

using namespace std;

/* Constructor function */
Reflector::Reflector(const std::string file) {
  check_file(file);
  get_config(file);
};

/* This function checks the configuration file */
void Reflector::check_file(const std::string filename) {
  ifstream in_stream;

  // open file                                                                                                                                                                         
  in_stream.open(filename.c_str());

  // if this has failed, there is an error opening the file                                                                                                                            
  if (extension(filename) != ".rf" || in_stream.fail()) {
    cerr << "Error opening reflector configuration file " << filename << ". Exiting..." << endl;
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

    // if this has failed, then a non-integer has been found                                                                                                                           
    if (in_stream.fail()) {
      cerr << "Reflector configuration file " << filename << " contains a non-numeric character " << test << ". Exiting..." << endl;
      throw  NON_NUMERIC_CHARACTER;
    }
    // return error code if invalid index found                                                                                                                                        
    if (test < 0 || test >= ALPHABET_SIZE) {
      cerr << "Reflector configuration file " << filename << " contains a number not in the alphabet " << test << ". Exiting..." << endl;
      throw INVALID_INDEX;
    }
    count++;
  }
  // return error code if the reflector doesn't contain 13 pairs                                                                                                                       
  if (count != ALPHABET_SIZE) {
    cerr << "Reflector configuration file " << filename << " does not contain 13 pairs of integers. Exiting..." << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  in_stream.close();
}

/* This function sets up the configuration of the reflector */
void Reflector::get_config(const std::string filename) {
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

    in_stream >> config[count];

    // return error code if double contact found                                                                                                                                       
    for (int i = 0; i < count; i++) {
      if (config[count] == config[i]) {
        cerr << "Reflector " << filename << " attempts to create a double contact. " << config[count] << " is paired twice. Exiting..." << endl;
        throw INVALID_REFLECTOR_MAPPING;
      }
    }
    count++;
  }
  in_stream.close();
}

/* This function maps the output of a given integer through the reflector */
int Reflector::map(int input) {
  // manipulate pairings of configuration array                                                                                                                                        
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (config[i] == input) {
      if (i % 2 == 0)
        return config[i+1];
      else if (i % 2 == 1)
        return config[i-1];
    }
  }
  return input;
}
