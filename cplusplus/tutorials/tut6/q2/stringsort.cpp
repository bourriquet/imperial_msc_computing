/*
Tutorial 6, Q 2
*/

#include <iostream>

using namespace std;

const int size = 80;

void string_sort(char a[]);
int minimum_from(char a[], int position);
void swap(char& first, char& second); 

int main() {

  char str[size];

  // user inputs a string
  cout << "Type in a string: ";
  cin.getline(str, size);

  string_sort(str);

  // output the sorted string
  cout << "The sorted string is: " << str << endl;

  return 0;
}

// sort a string, by swapping each element with the minimum element in the list
void string_sort(char a[]) {
  for (int count = 0; a[count] != '\0'; count++) {
    swap(a[count],a[minimum_from(a,count)]);
  }
}

// find the minimum element in the string, starting from the element at position
int minimum_from(char a[], int position) {
  int min_index = position;

  // if a smaller element is found, update the minimum index
  for (int count = position + 1; a[count] != '\0'; count++) {
    if (a[count] < a[min_index])
      min_index = count;
  }

  return min_index;
}

// swap first and second
void swap (char& first, char& second) {
  char temp = first;
  first = second;
  second = temp;
}
