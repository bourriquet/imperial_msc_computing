/*
Tutorial 6, Q 3
*/

#include <iostream>

using namespace std;

const int size = 80;

void no_reps(char a[]);
bool appeared_previously(char a[], const int pos);
void shuffle_up(char a[], int start);

int main() {

  char str[size];

  // user inputs a string
  cout << "Type in a string:" << endl;
  cin.getline(str, size);

  no_reps(str);

  // output the string with no repetitions
  cout << str << endl;

  return 0;
}

// sorts the array by shuffling up elements to replace elements that have appeared previously
void no_reps(char a[]) {
  for (int i = 0; a[i] != '\0'; i++) {
    if (appeared_previously(a,i)) {
      shuffle_up(a,i);
      i--;
    }
  }
}

// return true if the element at pos has occured previously in the array
bool appeared_previously(char a[], const int pos) {
  for (int i = 0; i < pos; i++) {
    if (a[i] == a[pos])
      return true;
  }

  return false;
}

// shuffles elements in the array up (once one has been deleted)
void shuffle_up(char a[], int start) {
  for (int i = start; a[i] != '\0'; i++) {
    a[i] = a[i+1];
  } 
}
