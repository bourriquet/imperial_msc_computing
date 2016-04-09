/*                                                                                                                                                                                     
  Filename: enigma.h                                                                                                                                                                   
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This header file contains the declarations of functions that don't belong to any class                                                                                               
*/

#define ALPHABET_SIZE 26

/* Declares functions defined in enigma.cpp  */
std::string extension(const std::string file);             // returns the file extension                                                                                               
void remainder(int& input);                                // returns a new position in the configuration array 
