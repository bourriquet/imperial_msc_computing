#include <iostream>
#include <cstring>

using namespace std;

int encode_character(char ch, char* braille) {

  strcpy(braille, "");
  int len = 6;

  if (isalpha(ch)) {

    if (isupper(ch)) {
	len += 6;
	strcpy(braille, ".....0");
	ch = tolower(ch);
    }

    switch(ch) {
    case 'a':
      strcat(braille, "0.....");
      return len;
    case 'b':
      strcat(braille, "00....");
      return len;
    case 'c':
      strcat(braille, "0..0..");
      return len;
    case 'd':
      strcat(braille, "0..00.");
      return len;
    case 'e':
      strcat(braille, "0...0.");
      return len;
    case 'f':
      strcat(braille, "00.0..");
      return len;
    case 'g':
      strcat(braille, "00.00.");
      return len;
    case 'h':
      strcat(braille, "00..0.");
      return len;
    case 'i':
      strcat(braille, ".0.0..");
      return len;
    case 'j':
      strcat(braille, ".0.00.");
      return len;
    case 'k':
      strcat(braille, "0.0...");
      return len;
    case 'l':
      strcat(braille, "000...");
      return len;
    case 'm':
      strcat(braille, "0.00..");
      return len;
    case 'n':
      strcat(braille, "0.000.");
      return len;
    case 'o':
      strcat(braille, "0.0.0.");
      return len;
    case 'p':
      strcat(braille, "0000..");
      return len;
    case 'q':
      strcat(braille, "00000.");
      return len;
    case 'r':
      strcat(braille, "000.0.");
      return len;
    case 's':
      strcat(braille, ".000..");
      return len;
    case 't':
      strcat(braille, ".0000.");
      return len;
    case 'u':
      strcat(braille, "0.0..0");
      return len;
    case 'v':
      strcat(braille, "000..0");
      return len;
    case 'w':
      strcat(braille, ".0.000");
      return len;
    case 'x':
      strcat(braille, "0.00.0");
      return len;
    case 'y':
      strcat(braille, "0.0000");
      return len;
    case 'z':
      strcat(braille, "0.0.00");
      return len;
    }
  }
  else if (isdigit(ch)) {
    len = 12;

    strcpy(braille, "..0000");

    switch(ch) {
    case '1':
      strcat(braille, "0.....");
      return len;
    case '2':
      strcat(braille, "00....");
      return len;
    case '3':
      strcat(braille, "0..0..");
      return len;
    case '4':
      strcat(braille, "0..00.");
      return len;
    case '5':
      strcat(braille, "0...0.");
      return len;
    case '6':
      strcat(braille, "00.0..");
      return len;
    case '7':
      strcat(braille, "00.00.");
      return len;
    case '8':
      strcat(braille, "00..0.");
      return len;
    case '9':
      strcat(braille, ".0.0..");
      return len;
    case '0':
      strcat(braille, ".0.00.");
      return len;
    }
  }

  else if (ispunct(ch)) {

    switch(ch) {
    case '.':
      strcpy(braille, ".0..00");
      return len;
    case ',':
      strcpy(braille, ".0....");
      return len;
    case ';':
      strcpy(braille, ".00...");
      return len;
    case '-':
      strcpy(braille, "..0..0");
      return len;
    case '!':
      strcpy(braille, ".00.0.");
      return len;
    case '?':
      strcpy(braille, ".00..0");
      return len;
    case '(':
    case ')':
      strcpy(braille, ".00.00");
      return len;
    }
  }

  else {

    strcat(braille, "......");
    return len;

  }

  return 0;

}

void encode(const char* plaintext, char* braille) {
  if (*plaintext == '\0')
    return;

  int length = encode_character(*plaintext, braille);

  encode((plaintext + 1), (braille + length));

}

void print_braille(const char* plaintext, ostream& out) {

  char braille[100];
  encode(plaintext, braille);


  // print first line                                                                               
  for (unsigned int i = 0; i < strlen(braille); i += 3) {
    out << braille[i];
    if (((i+3) % 6) == 0)
      out << " ";
  }
  out << endl;

  // print second line                                                                              
  for (unsigned int i = 1; i < strlen(braille); i += 3) {
    out << braille[i];
    if (((i+2) % 6) == 0)
      out << " ";
  }
  out << endl;

  // print third line                                                                               
  for (unsigned int i = 2; i < strlen(braille); i += 3) {
    out << braille[i];
    if (((i+1) % 6) == 0)
      out << " ";
  }
  out << endl;

  // print fourth line                                                                              
  for (unsigned int i = 0; i < strlen(plaintext); i++) {
    if (isupper(plaintext[i]) || isdigit(plaintext[i]))
      out << "   " << plaintext[i] << "  ";
    else
      out << plaintext[i] << "  ";
  }
  out << endl;

}
