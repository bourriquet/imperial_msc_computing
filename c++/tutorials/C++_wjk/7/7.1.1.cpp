#include <iostream>

using namespace std;

typedef int *IntPtrType;

int main() {

  IntPtrType ptr_a, ptr_b;
  int num_c = 4;
  int num_d = 7;

  ptr_a = &num_c;
  ptr_b = ptr_a;

  cout << *ptr_a << " " << *ptr_b << endl;

  ptr_b = &num_d;

  cout << *ptr_a << " " << *ptr_b << endl;

  *ptr_a = *ptr_b;

  cout << *ptr_a << " " << *ptr_b << endl;

  cout << num_c << " " << *&*&*&num_c << endl;

  return 0;
}
