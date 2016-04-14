#ifndef PIGLATIN
#define PIGLATIN

#include <iostream>

using namespace std;

int findFirstVowel(const char* word);
void translateWord(const char* english, char* piglatin);
void translateStream(istream& inputStream, ostream& outputStream);

#endif
