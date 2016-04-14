#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
void text_to_binary(const char* str, char* binary);
void binary_to_text(const char* binary, char* str);
void add_error_correction(const char* data, char* corrected);
int decode(const char* received, char* decoded);

#endif

