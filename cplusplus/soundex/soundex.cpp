#include <iostream>
#include <cstring>
#include <cctype>
#include "soundex.h"

using namespace std;

void encode(const char* surname, char* soundex) {

  soundex[0] = toupper(surname[0]);
  int soundex_count = 1;

  for (int i = 1; surname[i] != '\0'; i++) {
    if (code(surname[i]) >= '1' && code(surname[i]) <= '6') {
      if (i > 1 && code(surname[i]) == code(surname[i-1]))
        continue;
      else if (soundex_count < 4) {
        soundex[soundex_count] = code(surname[i]);
        soundex_count++;
      }
    }
  }
  for (int i = soundex_count; i < 4; i++) {
    soundex[i] = '0';
  }
  soundex[4] = '\0';
}

int compare(const char* one, const char* two) {

  if (strlen(one) == 0 && strlen(two) == 0)
    return 1;

  else if (*one == *two)
    return compare((one+1),(two+1));

  else if (*one != *two)
    return 0;

  return 0;

}

int count(const char* surname, const char* sentence) {

  char surnames[80], soundex1[5], soundex2[5];
  char *tok;

  int surname_count = 0;

  strcpy(surnames,sentence);
  encode(surname, soundex1);

  for (tok = strtok(surnames, ", ."); tok != NULL; tok = strtok(NULL, ", .")) {
    encode(tok, soundex2);

    if (compare(soundex1, soundex2))
      surname_count++;
  }

  return surname_count;

}

char code(const char input) {

  switch(input) {
  case 'b':
  case 'f':
  case 'p':
  case 'v':
    return '1';
    break;
  case 'c':
  case 'g':
  case 'j':
  case 'k':
  case 'q':
  case 's':
  case 'x':
  case 'z':
    return '2';
    break;
  case 'd':
  case 't':
    return '3';
    break;
  case 'l':
    return '4';
    break;
  case 'm':
  case 'n':
    return '5';
    break;
  case 'r':
    return '6';
    break;
  case 'a':
  case 'e':
  case 'h':
  case 'i':
  case 'o':
  case 'u':
  case 'w':
  case 'y':
    return '0';
    break;
  default:
    return '9';
    break;
  }
}
