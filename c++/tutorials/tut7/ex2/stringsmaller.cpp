#include <iostream>

using namespace std;

bool string_smaller(char a[], char b[]);
bool string_ptr_smaller(char *a, char *b);

int main() {

  char str1[10];
  char str2[10];

  // user input two strings
  cout << "Enter string 1:" << endl;
  cin.getline(str1, 10);
  cout << "Enter string 2:" << endl;
  cin.getline(str2, 10);

  // check using array function
  cout << "String 1 is ";
  if (!string_smaller(str1,str2))
    cout << "not ";
  cout << "smaller than string 2." << endl;

  // check using pointer function
  cout << "String 1 is ";
  if (!string_ptr_smaller(str1,str2))
    cout << "not ";
  cout << "smaller than string 2." << endl;

  return 0;

}

// array function - returns true if a is alphabetically smaller than b
bool string_smaller(char a[], char b[]) {
  int i = 0;

  // while neither string has ended...
  for (; (a[i] != '\0' &&  b[i] != '\0'); i++) {
    // a is bigger than b
    if (a[i] > b[i])
      return false;
    // a is less than b
    else if (a[i] < b[i])
      return true;
  }
  // if a has ended, it's smaller
  if (a[i] == '\0' && b[i] != '\0')
    return true;
  // else, a is not bigger
  else
    return false;
}

// pointer function - returns true if a is alphabetically smaller than b
bool string_ptr_smaller(char* a, char* b) {

  // while neither string has ended
  for (; (*a != '\0' && *b != '\0'); a++, b++) {
    // a is bigger than b
    if (*a > *b)
      return false;
    // a is less than b
    else if (*a < *b)
      return true;
  }

  // if a has ended, it's smaller
  if (*a == '\0' && *b != '\0')
    return true;
  // else, a is bigger
  else
    return false;
}
