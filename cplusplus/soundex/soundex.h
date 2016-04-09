#ifndef SOUNDEX
#define SOUNDEX

void encode(const char* surname, char* soundex);
int compare(const char* one, const char* two);
int count(const char* surname, const char* sentence);
char code(const char input);

#endif
