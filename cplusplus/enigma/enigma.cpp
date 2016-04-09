/*                                                                                                                                                                                     
  Filename: enigma.cpp                                                                                                                                                                 
  Author: lc3311                                                                                                                                                                       
  Last updated: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
  This implementation file contains the function definitions of functions not specific                                                                                                 
  to one class                                                                                                                                                                         
*/

#include <string>
#include "enigma.h"

/* This function returns the extension of a filename */
std::string extension(const std::string file) {
  std::string extension = "";

  // get the characters after a '.' - ** THIS WOULDN'T WORK IF A FILE NAME HAD TWO DOTS E.G example.rf.rf **                                                                           
  for (unsigned int i = 0; i < file.length(); i++) {
    if (file[i] == '.') {
      for (unsigned int j = i; j < file.length(); j++) {
	extension += file[j];
      }
    }
  }
  return extension;
}

/* This function alters the position in the configuration array when it is < 0 or > 25 */
void remainder(int& input) {
  while (input < 0)
    input += ALPHABET_SIZE;
  while (input >= ALPHABET_SIZE)
    input -= ALPHABET_SIZE;
}
