#include <iostream>

using namespace std;

bool string_smaller(char a[], char b[]);
bool string_ptr_smaller(char *a, char *b);

int main() {

  char str1[10];
  char str2[10];

  cout << "Enter string 1:" << endl;
  cin.getline(str1, 10);
  cout << "Enter string 2:" << endl;
  cin.getline(str2, 10);

  cout << "String 1 is ";
  if (!string_smaller(str1,str2))
    cout << "not ";
  cout << "smaller than string 2." << endl;

  cout << "String 1 is ";
  if (!string_ptr_smaller(str1,str2))
    cout << "not ";
  cout << "smaller than string 2." << endl;

  return 0;

}

bool string_smaller(char a[], char b[]) {
  int i = 0;

  for (; (a[i] != '\0' &&  b[i] != '\0'); i++) {
    if (a[i] > b[i])
      return false;
    else if (a[i] < b[i])
      return true;
  }
  if (a[i] == '\0' && b[i] != '\0')
    return true;
  else
    return false;
}

bool string_ptr_smaller(char* a, char* b) {

  for (; (*a != '\0' && *b != '\0'); a++, b++) {
    if (*a > *b)
      return false;
    else if (*a < *b)
      return true;
  }
  if (*a == '\0' && *b == '\0')
    return true;
  else
    return false;
}
