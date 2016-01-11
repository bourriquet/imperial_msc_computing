#include <iostream>

using namespace std;

const int MAX = 11;

void quick_sort(int list[MAX], int left, int right);
void swap(int& first, int& second);
void display(int a[], int length);

int main() {

  int list[MAX];
  
  for (int i = 0; i < MAX; i++) {
    cout << "Enter value of element" << i <<  ": ";
    cin >> list[i];
  }

  cout << "Before quick sort: " << endl << endl;
  display(list, MAX);
  cout << endl << endl;

  quick_sort(list, 0, MAX - 1);
  cout << "After quick sort: " << endl << endl;
  display(list, MAX);
  cout << endl;

  return 0;
}

void quick_sort(int list[], int left, int right) {

  int pivot, left_arrow, right_arrow;

  left_arrow = left;
  right_arrow = right;
  pivot = list[(left+right)/2];

  do {
    while (list[right_arrow] > pivot)
      right_arrow--;
    while (list[left_arrow] < pivot)
      left_arrow++;
    if (left_arrow <= right_arrow) {
      swap(list[left_arrow], list[right_arrow]);
      left_arrow++;
      right_arrow--;
    }
  } while (right_arrow >= left_arrow);

  if (left < right_arrow)
    quick_sort(list, left, right_arrow);
  if (left_arrow < right)
    quick_sort(list, left_arrow, right);

}
void swap(int& first, int& second) {
  int temp = first;
  first = second;
  second = temp;
}

void display(int a[], int length) {
  for (int count = 0; count < length; count++) {
    cout << a[count] << " ";
  }
  cout <<  endl;
}
