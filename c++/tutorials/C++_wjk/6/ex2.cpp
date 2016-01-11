#include <iostream>

using namespace std;

const int size = 80;

void string_sort(char a[]);
int minimum_from(char a[], int position);
void swap(char& first, char& second); 

int main() {

  char str[size];

  cout << "Type in a string: ";
  cin.getline(str, size);

  string_sort(str);

  cout << "The sorted string is: " << str << endl;

  return 0;
}


void string_sort(char a[]) {
  for (int count = 0; a[count] != '\0'; count++) {
    swap(a[count],a[minimum_from(a,count)]);
  }
}

int minimum_from(char a[], int position) {
  int min_index = position;
  for (int count = position + 1; a[count] != '\0'; count++) {
    if (a[count] < a[min_index])
      min_index = count;
  }
  return min_index;
}

void swap (char& first, char& second) {
  char temp = first;
  first = second;
  second = temp;
}
