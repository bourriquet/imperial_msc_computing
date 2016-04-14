#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

#include "piglatin.h"

using namespace std;

int findFirstVowel(const char* word) {

  for (unsigned int i = 0; i < strlen(word); i++) {

    char ch = tolower(word[i]);

    switch(ch) {
    case 'y':
      // if y is first or last, not a vowel                                                         
      if ((i == 0) || word[i+1] == '\0')
        break;
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return i;
    }
  }

  return -1;
}

void translateWord(const char* english, char* piglatin) {

  int index = findFirstVowel(english);
  char temp1[100];
  char temp2[100];

  strcpy(piglatin, "");

  if (index == 0) {
    strcpy(piglatin,english);
    strcat(piglatin, "way");
  }

  else if (index == -1) {
    strcpy(piglatin,english);

    if (!isdigit(english[0]))
      strcat(piglatin, "ay");
  }

  else {
    for (unsigned int i = index; i < strlen(english); i++) {
      temp1[i - index] = tolower(english[i]);
    }
    temp1[strlen(english) - index] = '\0';
    strcpy(piglatin, temp1);

    for (int i = 0; i < index; i++) {
      temp2[i] = tolower(english[i]);
    }
    temp2[index] = '\0';
    strcat(piglatin, temp2);
    strcat(piglatin, "ay");
  }

  if (isupper(english[0]))
    piglatin[0] = toupper(piglatin[0]);

}

void translateStream(istream& inputStream, ostream& outputStream) {

  char word[64];
  char translated[64];
  char punc;
  bool punct = false;

  while (inputStream >> word) {

    if (ispunct(word[strlen(word)-1])) {
      punct = true;
      punc = word[strlen(word)-1];
      word[strlen(word)-1] = '\0';
    }

    if (ispunct(word[0])) {
      punc = word[0];
      for (unsigned int i = 1; i < (strlen(word) - 1); i++) {
        word[i-1] = word[i];
      }
      word[strlen(word) - 1] = '\0';
      outputStream << punc;
    }
    translateWord(word, translated);

    if (punct) {
      int len = strlen(translated);
      translated[len] = punc;
      translated[len+1] = '\0';
      punct = false;
    }

    outputStream << translated;

    if (inputStream.peek() == '\n')
      outputStream << '\n';
    else
      outputStream << " ";

  }
  outputStream << endl;

}
