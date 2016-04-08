/*
Tutorial 8, Q 4
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int binary_search(int value, int list[], int first, int last);

int main() {
  int listy[11];
  
  listy[0] = 2;
  listy[1] = 2;
  listy[2] = 3;
  listy[3] = 5;
  listy[4] = 8;
  listy[5] = 14;
  listy[6] = 16;
  listy[7] = 22;
  listy[8] = 22;
  listy[9] = 24;
  listy[10] = 30;

  int search;

  cout << "Enter a value to search: " << endl;
  cin >> search;

  if (binary_search(search,listy,0,10) == -1) {
    cout << "That value isn't in the list." << endl;
    exit(1);
  }
  cout << "The value " << search << " is at position " << binary_search(search,listy,0,11) << endl;
}

int binary_search(int value, int list[], int first, int last) {
  int pivot = (last + first) / 2;
  
  if (list[pivot] == value) {
    return pivot;
  }
  if (first > last) {
    return -1;
  }
  else if (list[pivot] > value) {
    return binary_search(value, list, first, pivot-1);
  }
  else if (list[pivot] < value) {
    return binary_search(value, list, pivot+1, last);
  }
  else {
    return -1;
  }
}
