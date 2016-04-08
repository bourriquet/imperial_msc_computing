/*
Tutorial 2, Q 4

Implementation file
*/

#include <iostream>
#include <iomanip>

#include "temperature.h"

using namespace std;

// converts F into C
double celsius_of(int fahr) {
  return (((double)fahr - 32) * (5.0 / 9));
}

// converts F into K
double absolute_value_of(int fahr) {
  return celsius_of(fahr) + 273.15;
}

// prints a message
void print_preliminary_message() {
  cout << "This program gives a table of F, C and K temperatures." << endl << e$
}

// user input
void input_table_specifications(int& lower, int& upper, int& step) {
  cout << "Enter a lower F temp." << endl;
  cin >> lower;

  cout << "Enter an upper F temp." << endl;
  cin >> upper;

  cout << "Enter a step F value." << endl;
  cin >> step;
}

// prints a message
void print_message_echoing_input(int lower, int upper, int step) {
  cout << "The table of temperatures starting at " << lower << " and ending at $
  cout << " with a step value of " << step << " is as follows..." << endl << en$
}
