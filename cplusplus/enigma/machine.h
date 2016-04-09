/*                                                                                                                                                                                     
  Filename: machine.h                                                                                                                                                                  
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This header file contains the declarations of the Machine class - implementations in machine.cpp                                                                                     
*/

#ifndef MACHINE
#define MACHINE

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

class Machine {

 private:
  Plugboard *plugboard;                                    // creates a plugboard                                                                                                      
  Reflector *reflector;                                    // creates a reflector                                                                                                      
  int num_rotors;                                          // number of rotors in the machine                                                                                          
  Rotor **rotors;                                          // an array of rotors                                                                                                       
  int *positions;                                          // an array of rotor positions                                                                                              
  void get_rotor_positions(const std::string filename);    // gets the rotor positions                                                                                                 
  void shift();                                            // shifts the rotors                                                                                                        

 public:
  Machine(int argc, char **argv);                          // constructor                                                                                                              
  int encrypt(int input);                                  // encrypts an input digit                                                                                                  
};

#endif
