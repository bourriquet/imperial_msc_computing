#ifndef BRAILLE
#define BRAILLE

int encode_character(char ch, char* braille);
void encode(const char* plaintext, char* braille);
void print_braille(const char* plaintext, ostream& out);

#endif
