/*
Tutorial 3, Q 1

Main program file
*/

#include <iostream>
#include <iomanip>
#include "temperature.h"

using namespace std;

// function definitions in temperature.cpp

int main() {

  int lower, upper, step;

  print_preliminary_message();
  input_table_specifications(lower, upper, step);
  print_message_echoing_input(lower, upper, step);
  print_table(lower, upper, step);

  return 0;
}
