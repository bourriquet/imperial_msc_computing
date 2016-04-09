/*                                                                                                                                                                                     
  Filename: plugboard                                                                                                                                                                  
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This header file contains the declarations of the Plugboard class - implementations in plugboard.cpp                                                                                 
*/

#ifndef PLUGBOARD
#define PLUGBOARD

class Plugboard {

 private:
  int number_of_contacts;                                 // number of integers in configuration file                                                                                  
  int *config;                                            // an array containing the configuration                                                                                     
  void check_file(const std::string file);                // checks the file for errors                                                                                                
  void get_config(const std::string filename);            // gets the config of the plugboard                                                                                          

 public:
  Plugboard(const std::string file);                      // constructor                                                                                                               
  int map(int input);                                     // maps an input integer                                                                                                     
};

#endif
