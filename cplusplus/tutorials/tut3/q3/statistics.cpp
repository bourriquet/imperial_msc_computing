/*
Tutorial 3, Q 3

Implementation file
*/

#include <iostream>
#include <cmath>
#include "statistics.h"

using namespace std;

double num1, num2, num3, num4;

//Functions for computing averages
double average(double num1) {
  return num1;
}
double average(double num1, double num2) {
  return 0.5 * (num1 + num2);
}
double average(double num1, double num2, double num3) {
  return (num1 + num2 + num3) / 3;
}
double average(double num1, double num2, double num3, double num4) {
  return 0.25 * (num1 + num2 + num3 + num4);
}

//Functions for computing standard deviation
double standard_deviation(double num1) {
  return 0;
}
double standard_deviation(double num1, double num2) {
  double arg1, arg2;
  arg1 = (num1 - average(num1, num2)) * (num1 - average(num1, num2));
  arg2 = (num2 - average(num1, num2)) * (num2 - average(num1, num2));
  return sqrt(average(arg1, arg2));
}
double standard_deviation(double num1, double num2, double num3) {
  double arg1, arg2, arg3;
  arg1 = (num1 - average(num1, num2, num3)) * (num1 - average(num1, num2, num3));
  arg2 = (num2 - average(num1, num2, num3)) * (num2 - average(num1, num2, num3));
  arg3 = (num3 - average(num1, num2, num3)) * (num3 - average(num1, num2, num3));
  return sqrt(average(arg1, arg2, arg3));
}
double standard_deviation(double num1, double num2, double num3, double num4) {
  double arg1, arg2, arg3, arg4;
  arg1 = (num1 - average(num1, num2, num3, num4)) * (num1 - average(num1, num2, num3, num4));
  arg2 = (num2 - average(num1, num2, num3, num4)) * (num2 - average(num1, num2, num3, num4));
  arg3 = (num3 - average(num1, num2, num3, num4)) * (num3 - average(num1, num2, num3, num4));
  arg4 = (num4 - average(num1, num2, num3, num4)) * (num4 - average(num1, num2, num3, num4));
  return sqrt(average(arg1, arg2, arg3, arg4));
}
