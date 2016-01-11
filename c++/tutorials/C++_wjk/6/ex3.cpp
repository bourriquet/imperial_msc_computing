#include <iostream>

using namespace std;

const int size = 80;

void no_reps(char a[]);
bool appeared_previously(char a[], const int pos);
void shuffle_up(char a[], int start);

int main() {

  char str[size];

  cout << "Type in a string:" << endl;
  cin.getline(str, size);

  no_reps(str);

  cout << str << endl;


  return 0;

}

void no_reps(char a[]) {
  for (int i = 0; a[i] != '\0'; i++) {
    if (appeared_previously(a,i)) {
      shuffle_up(a,i);
      i--;
    }
  }
}

bool appeared_previously(char a[], const int pos) {
  for (int i = 0; i < pos; i++) {
    if (a[i] == a[pos])
      return true;
  }
  return false;
}

void shuffle_up(char a[], int start) {
  for (int i = start; a[i] != '\0'; i++) {
    a[i] = a[i+1];
  }
}
