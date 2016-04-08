/*
Tutorial 3, Q 3

Main program file
*/

#include <iostream>
#include <stdlib.h>
#include "statistics.h"

using namespace std;

double no1, no2, no3, no4;
int req;

void num_values();
void one_num();
void two_num();
void three_num();
void four_num();

int main() {
  cout << "This program computes the average and standard deviation of 1, 2, 3 or 4 numbers." << endl << endl;
  
  //How many values the user wants
  num_values();

  //Carry on asking until the user quits
  while (req != 0) {
    if (req == 1) {
      one_num();
    } else if (req == 2) {
      two_num();
    } else if (req == 3) {
      three_num();
    } else if (req == 4) {
      four_num();
    } else {
      cout << "Sorry, this program can only test 1, 2, 3 or 4 values." << endl << endl;
    }
    num_values();
  }
  cout << "Finished testing 'statistics.h' header file" << endl;

  return 0;
}

// ask the user how many values
void num_values() {
  cout << "Do you wish to test 1, 2, 3 or 4 values (enter 0 to end the program): " << endl;
  cin >> req;
  cout << endl << endl;
}
void one_num() {
  cout << "Number: " << endl;
  cin >> no1;
  cout << "Average: " << average(no1) << endl;
  cout << "Standard deviation: " << standard_deviation(no1) << endl;
}
void two_num() {
  cout << "First number: " << endl;
  cin >> no1;
  cout << "Second number: " << endl;
  cin >> no2;
  cout << "Average: " << average(no1, no2) << endl;
  cout << "Standard deviation: " << standard_deviation(no1, no2) << endl;
}
void three_num() {
  cout << "First number: " << endl;
  cin >> no1;
  cout << "Second number: " << endl;
  cin >> no2;
  cout << "Third number: " <<endl;
  cin >> no3;
  cout << "Average: " << average(no1, no2, no3) << endl;
  cout << "Standard deviation: " << standard_deviation(no1, no2, no3) << endl;
}
void four_num() {
  cout << "First number: " << endl;
  cin >> no1;
  cout << "Second number: " << endl;
  cin >> no2;
  cout << "Third number: " << endl;
  cin >> no3;
  cout << "Fourth number: " << endl;
  cin >> no4;
  cout << "Average: " << average(no1, no2, no3, no4) << endl;
  cout << "Standard deviation: " << standard_deviation(no1, no2, no3, no4) << endl;
}
