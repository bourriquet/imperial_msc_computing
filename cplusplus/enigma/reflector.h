/*                                                                                                                                                                                     
  Filename: reflector.h                                                                                                                                                                
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This header file contains the declarations of the Reflector class - implementations in reflector.cpp                                                                                 
*/

#ifndef REFLECTOR
#define REFLECTOR

class Reflector {

 private:
  int config[ALPHABET_SIZE];                                         // an array containing the configuration                                                                          
  void check_file(const std::string filename);            // checks the file for errors                                                                                                
  void get_config(const std::string filename);            // gets the config of the reflector                                                                                          

 public:
  Reflector(const std::string file);                      // constructor                                                                                                               
  int map(int input);                                     // maps an input integer                                                                                                     
};

#endif

