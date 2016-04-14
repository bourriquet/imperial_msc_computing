#include <iostream>
#include <cstring>
#include "correct.h"

using namespace std;

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1)
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

void text_to_binary(const char* str, char* binary) {

  if (*str == '\0')
    return;

  char bin[8];

  ascii_to_binary(*str, bin);
  strcat(binary,bin);

  text_to_binary((str + 1), binary);

}

void binary_to_text(const char* binary, char* str) {

  if (*binary == '\0')
    return;

  char temp[512];

  strcpy(temp, binary);
  temp[8] = '\0';

  *str = binary_to_ascii(temp);

  binary_to_text((binary + 8), (str + 1));

}

void add_error_correction(const char* data, char* corrected) {

  if (*data == '\0') {
    *corrected = '\0';
    return;
  }

  int d[4];
  int c[3];

  for (int i = 0; i < 4; i++) {
    d[i] = (static_cast<int>(*(data + i))) - 48;
  }

  c[0] = ((d[0] + d[1] + d[3]) % 2);
  c[1] = ((d[0] + d[2] + d[3]) % 2);
  c[2] = ((d[1] + d[2] + d[3]) % 2);

  *(corrected) = '0' + c[0];
  *(corrected+1) = '0' + c[1];
  *(corrected+2) = '0' + d[0];
  *(corrected+3) = '0' + c[2];
  *(corrected+4) = '0' + d[1];
  *(corrected+5) = '0' + d[2];
  *(corrected+6) = '0' + d[3];

  add_error_correction(data + 4, corrected + 7);

}

int decode(const char* received, char* decoded) {

  if (*received == '\0') {
    *decoded = '\0';
    return 0;
  }

  int p[3];
  int b[7];

  for (int i = 0; i < 7; i++) {
    b[i] = (static_cast<int>(*(received + i))) - 48;
  }

  p[0] = ((b[3] + b[4] + b[5] + b[6]) % 2);
  p[1] = ((b[1] + b[2] + b[5] + b[6]) % 2);
  p[2] = ((b[0] + b[2] + b[4] + b[6]) % 2);

  *(decoded) = '0' + b[2];
  *(decoded + 1) = '0' + b[4];
  *(decoded + 2) = '0' + b[5];
  *(decoded + 3) = '0' + b[6];

  if ((p[0] + p[1] + p[2]) == 0)
    return decode((received + 7), (decoded + 4));

  else {
    int error_pos = (p[0] * 4) + (p[1] * 2) + p[2] - 1;

    switch(error_pos) {
    case 2:
      *(decoded) = ((*(decoded) + 1) % 2) + '0';
      break;
    case 4:
      *(decoded + 1) = ((*(decoded + 1) + 1) % 2) + '0';
      break;
    case 5:
      *(decoded + 2) = ((*(decoded + 2) + 1) % 2) + '0';
      break;
    case 6:
      *(decoded + 3) = ((*(decoded + 3) + 1) % 2) + '0';
      break;
    default:
      return decode((received + 7), (decoded + 4));
    }
    return 1 + decode((received + 7), (decoded + 4));
  }
}
