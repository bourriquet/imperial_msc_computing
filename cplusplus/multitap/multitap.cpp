#include <iostream>
#include <cctype>
#include <cstring>
#include "multitap.h"

using namespace std;

int encode_character(const char ch, char* multitap) {

  char chr;

  strcpy(multitap, "");

  chr = tolower(ch);

  switch(chr) {

  case 'a':
    strcpy(multitap, "2");
    break;
  case 'b':
    strcpy(multitap, "22");
    break;
  case 'c':
    strcpy(multitap, "222");
    break;
  case 'd':
    strcpy(multitap, "3");
    break;
  case 'e':
    strcpy(multitap, "33");
    break;
  case 'f':
    strcpy(multitap, "333");
    break;
  case 'g':
    strcpy(multitap, "4");
    break;
  case 'h':
    strcpy(multitap, "44");
    break;
  case 'i':
    strcpy(multitap, "444");
    break;
  case 'j':
    strcpy(multitap, "5");
    break;
  case 'k':
    strcpy(multitap, "55");
    break;
  case 'l':
    strcpy(multitap, "555");
    break;
  case 'm':
    strcpy(multitap, "6");
    break;
  case 'n':
    strcpy(multitap, "66");
    break;
  case 'o':
    strcpy(multitap, "666");
    break;
  case 'p':
    strcpy(multitap, "7");
    break;
  case 'q':
    strcpy(multitap, "77");
    break;
  case 'r':
    strcpy(multitap, "777");
    break;
  case 's':
    strcpy(multitap, "7777");
    break;
  case 't':
    strcpy(multitap, "8");
    break;
  case 'u':
    strcpy(multitap, "88");
    break;
  case 'v':
    strcpy(multitap, "888");
    break;
  case 'w':
    strcpy(multitap, "9");
    break;
  case 'x':
    strcpy(multitap, "99");
    break;
  case 'y':
    strcpy(multitap, "999");
    break;
  case 'z':
    strcpy(multitap, "9999");
    break;

  case '.':
    strcpy(multitap, "1");
    break;
  case ',':
    strcpy(multitap, "11");
    break;
  case '!':
    strcpy(multitap, "111");
    break;
  case '?':
    strcpy(multitap, "1111");
    break;
  case ' ':
    strcpy(multitap, "0");
    break;

  case '0':
    strcpy(multitap, "*0");
    break;
  case '1':
    strcpy(multitap, "*1");
    break;
  case '2':
    strcpy(multitap, "*2");
    break;
  case '3':
    strcpy(multitap, "*3");
    break;
  case '4':
    strcpy(multitap, "*4");
    break;
  case '5':
    strcpy(multitap, "*5");
    break;
  case '6':
    strcpy(multitap, "*6");
    break;
  case '7':
    strcpy(multitap, "*7");
    break;
  case '8':
    strcpy(multitap, "*8");
    break;
  case '9':
    strcpy(multitap, "*9");
    break;
  }

  return strlen(multitap);
}

void encode(const char* plaintext, char* multitap) {

  char last[5];
  char temp[5];

  bool upper = false;

  strcpy(last, "");
  strcpy(multitap, "");

  if (isupper(*plaintext) && (*plaintext != ' ')) {
    strcat(multitap, "#");
    upper = true;
  }

  encode_character(*plaintext, temp);
  strcat(multitap, temp);

  for (int i = 1; plaintext[i] != '\0'; i++) {
    strcpy(temp, "");

    encode_character(plaintext[i], temp);

    if (last[0] == temp[0])
      strcat(multitap, "|");

    if ((upper == true) && !(isupper(plaintext[i]))) {
      strcat(multitap, "#");
      upper = false;
    }
    else if ((upper == false) && (isupper(plaintext[i]))) {
      strcat(multitap, "#");
      upper = true;
    }

    strcat(multitap, temp);

    strcpy(last, temp);
  }
}
