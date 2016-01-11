#include <iostream>
#include <fstream>

using namespace std;

int main() {

  char character;
  int number = 51;

  ofstream out;
  ifstream in1;
  ifstream in2;

  out.open("Integers");
  for (int i = 0; i < 5; i++) {
    out << number++ << ' ';
  }
  out.close();

  in1.open("Integers");
  int count = 0;
  in1 >> number;
  while (!in1.eof()) {
    count++;
    in1 >> number;
  }
  in1.close();
  cout << "There are " << count << " integers in the file" << endl;

  in2.open("Integers");
  count = 0;
  in2 >> character;
  while (!in2.eof()) {
    count++;
    in2 >> character;
  }
  in2.close();
  cout << "There are " << count << " characters in the file" << endl;

  return 0;


}
