#include <iostream>
#include <cmath>

#include "array.h"

using namespace std;

void input_array(int a[], int n) {
  for (int i = 0; i < n; i++) {
    cout << "Enter a value for index " << i << endl;
    cin >> a[i];
  }
}

void display_array(int a[], int n) {
  for (int i = 0; i < n; i++) {
    cout << "The value at index " << i << "is: " << a[i] << endl;
  }
}

void copy_array(int a1[],int a2[],int n) {
  for (int i = 0; i < n; i++) {
    a1[i] = a2[i];
  }
}

double average(int a[], int n) {
  double total = 0;
  for (int i = 0; i < n; i++) {
    total += a[i];
  }
  return total/n;
}

double std_dev(int a[], int n) {
  double avg = average(a,n);
  double total = 0;
  for (int i = 0; i < n; i++) {
    total += ((a[i] - avg) * (a[i] - avg));
  }
  double new_avg = total/n;
  return sqrt(new_avg);
}
