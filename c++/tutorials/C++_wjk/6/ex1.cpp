#include <iostream>

#include "array.h"

using namespace std;

int main() {

  const int size = 5;

  int first[size];
  int second[size];

  input_array(first,size);
  input_array(second,size);

  display_array(first,size);
  cout << endl;
  display_array(second,size);
  cout << endl;

  copy_array(first,second,3);
  display_array(first,size);
  cout << endl;

  cout << std_dev(first,size) << endl;
  cout << std_dev(second,size) << endl;

  return 0;

}
