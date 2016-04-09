#include <iostream>
#include <cstring>
#include "substring.h"

using namespace std;

// returns the position in the second string of the first string (as a substring)                                                                                                      
int substring_position(const char* string1, const char* string2) {

  // an empty first string is a substring of all strings                                                                                                                               
  if (strlen(string1) == 0)
    return 0;

  // if second string is empty, the first string is not a substring                                                                                                                    
  if (strlen(string2) == 0)
    return -1;

  // add 1 to previous position                                                                                                                                                        
  if (!is_prefix(string1, string2)) {
    int no_error = substring_position(string1, string2 + 1);
    if (no_error >= 0)
      return no_error + 1;
  }

  // base case                                                                                                                                                                         
  else if (is_prefix(string1, string2))
    return 0;

  // ITERATIVE VERSION                                                                                                                                                                 
  /*                                                                                                                                                                                   
  for (int i = 0; string2[i] != '\0'; i++) {                                                                                                                                           
    if (is_prefix(string1, string2 + i)) {                                                                                                                                             
      return i;                                                                                                                                                                        
    }                                                                                                                                                                                  
  }                                                                                                                                                                                    
  */

  return -1;
}
