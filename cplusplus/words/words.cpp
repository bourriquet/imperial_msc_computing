#include <iostream>
#include <cstring>
#include "words.h"

using namespace std;

void reverse(const char* str1, char* str2) {

  int len = strlen(str1);
  str2[len] = '\0';

  for (int i = 0; str1[i] != '\0'; i++) {
    len--;
    str2[len] = str1[i];
  }

}

int compare(const char* one, const char* two) {

  if ((strlen(one) == 0) && (strlen(two) == 0))
    return 1;

  if (strlen(one) == 0)
    return compare(one, two + 1);
  if (strlen(two) == 0)
    return compare(one + 1, two);

  int first = static_cast<int>(*one);
  int second = static_cast<int>(*two);

  if (first >= 65 && first <= 90)
    first += 32;
  if (second >= 65 && second <= 90)
    second += 32;

  if (!(first >= 97 && first <= 122))
    return compare(one + 1, two);

  if (!(second >= 97 && second <= 122))
    return compare(one, two + 1);

  if (first != second)
    return 0;

  if (first == second)
    return compare(one + 1, two + 1);

  return 1;
}

int palindrome(const char* sentence) {

  char rev_sentence[strlen(sentence)];

  reverse(sentence, rev_sentence);

  if (compare(sentence, rev_sentence))
    return 1;

  return 0;
}

int anagram(const char* str1, const char* str2) {

  char string1[strlen(str1)];
  char string2[strlen(str2)];

  strcpy(string1, str1);
  strcpy(string2, str2);

  remove_rubbish(string1);
  remove_rubbish(string2);

  for (unsigned int i = 0; i < strlen(str1); i++) {
    find_smallest(string1, i);
  }
  for (unsigned int i = 0; i < strlen(str2); i++) {
    find_smallest(string2, i);
  }

  if (compare(string1, string2))
    return 1;

  return 0;
}

// removes all punctuation and converts upper case to lower case
void remove_rubbish(char* str) {

  for (unsigned int i = 0; i < strlen(str); i++) {
    int chr = static_cast<int>(str[i]);

    if (chr >= 65 && chr <= 90) {
      chr += 32;
      str[i] = static_cast<char>(chr);
    }

    else if (!(chr >= 97 && chr <= 122)) {
      str[i] = ' ';
    }
  }
}

// orders the string by character
int find_smallest(char* str, int start) {

  int position = start;
  for (unsigned int i = start + 1; i < strlen(str); i++) {
    if (str[i] > str[position])
      position = i;
  }
  swap(str[start], str[position]);
  return position;
}
void swap(char& first, char& second) {
  char temp = first;
  first = second;
  second = temp;
}
