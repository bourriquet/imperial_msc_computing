/*                                                                                                                                                                                     
  Filename: rotor.h                                                                                                                                                                    
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This header file contains the declarations of the Rotor class - implementations in rotor.cpp                                                                                         
*/

#ifndef ROTOR
#define ROTOR

#include "enigma.h"

class Rotor {

 private:
  int config[ALPHABET_SIZE];                                   // an array containing the configuration                                                                                
  int number_of_notches;                                  // number of notches specified                                                                                               
  int *notches;                                           // an array of notch positions                                                                                               
  int current_position;                                   // i.e the letter at the 'top' of the rotor                                                                                  
  void check_file(const std::string file);                     // check the configuration file                                                                                         
  void get_initial_config(const std::string filename);         // gets the initial config of the rotor                                                                                 

 public:
  Rotor(const std::string file, const int starting_position);  // constructor                                                                                                          
  void shift_up();                                             // rotates the rotor one position                                                                                       
  int map_forwards(int input);                                 // maps an input when the current is flowing right to left                                                              
  int map_backwards(int input);                                // maps an input when the current is flowing left to right                                                              
  bool shift_left();                                           // returns true if the rotor to the left needs to shift up                                                              
  int get_current_position();                                  // returns the current position of the rotor as it is private                                                           
};

#endif
