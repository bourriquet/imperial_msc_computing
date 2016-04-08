/*
Tutorial 3, Q 1

Main program file
*/

#include "temperature.h"

using namespace std;

int main() {

  int lower, upper, step;

  print_preliminary_message();
  input_table_specifications(lower, upper, step);
  print_message_echoing_input(lower, upper, step);
  print_table(lower, upper, step);

  return 0;
}
