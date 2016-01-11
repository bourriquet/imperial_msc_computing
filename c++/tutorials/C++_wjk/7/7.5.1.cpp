#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

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

int main() {

  Node_ptr my_list = NULL;
  assign_list(my_list);
  cout << "The list is now:" << endl;
  print_list(my_list);
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
