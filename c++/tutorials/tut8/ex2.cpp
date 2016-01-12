#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// program from original notes/tut7

const int SIZE = 80;

struct Node;
typedef Node *Node_ptr;

struct Node {
  char word[SIZE];
  Node_ptr ptr_next;
};

void assign_list(Node_ptr& a_list);
void assign_new_node(Node_ptr& a_node);
void print_list(Node_ptr a_node);
void print_list_forwards(Node_ptr a_node);
void print_list_backwards(Node_ptr a_node);
void print_back(Node_ptr a_node);

int main() {

  Node_ptr my_list = NULL;
  assign_list(my_list);

  cout << "The list forwards is:" << endl;
  print_list_forwards(my_list);
  cout << endl << endl;

  cout << "The list backwards is:" << endl;
  print_list_backwards(my_list);
  cout << endl << endl;

  print_back(my_list);
  cout << endl;

  return 0;
}

void assign_list(Node_ptr& a_list) {
  Node_ptr current_node, last_node;

  assign_new_node(a_list);

  cout << "Enter first word (or '.' to end list)" << endl;
  cin >> a_list->word;

  if (!strcmp(".", a_list->word)) {
    delete a_list;
    a_list = NULL;
  }
  current_node = a_list;

  while (current_node != NULL) {
    assign_new_node(last_node);
    cout << "Enter next word (or '.' to end list):" << endl;
    cin >> last_node->word;
    if (!strcmp(".",last_node->word)) {
      delete last_node;
      last_node = NULL;
    }
    current_node->ptr_next = last_node;
    current_node = last_node;
  }
}

void assign_new_node(Node_ptr& a_node) {
  a_node = new (nothrow) Node;
  if (a_node == NULL) {
    cerr << "No more memory" << endl;
    exit(1);
  }
}

void print_list(Node_ptr a_node) {
  while (a_node != NULL) {
    cout << a_node->word << " ";
    a_node = a_node->ptr_next;
  }
}

// prints linked list forwards using recursion
void print_list_forwards(Node_ptr a_node) {
  if (a_node != NULL) {
    cout << a_node->word << " ";
    print_list_forwards(a_node->ptr_next);
  }
}

// prints linked list backwards using recursion
void print_list_backwards(Node_ptr a_node) {
  if (a_node != NULL) {
    print_list_backwards(a_node->ptr_next);
    cout << a_node->word << " ";
  }
}

// prints linked list backwards iteratively
void print_back(Node_ptr a_node) {

  Node_ptr current_node;
  current_node = a_node;
  
  // count the number of nodes in the linked list
  int count = 0;
  while (current_node != NULL) {
    count++;
    current_node = current_node->ptr_next;
  }

  current_node = a_node;

  // start at the end and print each one
  for (int i = count; i >= 0; i--) {
    int j = 0;
    while (current_node != NULL) {
      //cout << current_node->word << endl;
      current_node = current_node->ptr_next;
      if (j == i-1)
	cout << current_node->word << endl;
      j++;
    }
    //    cout << current_node->word;
    current_node = a_node;
  }
}
