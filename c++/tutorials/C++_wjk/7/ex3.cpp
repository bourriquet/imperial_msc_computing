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
void add_after(Node_ptr& list, char a_word[], char word_after[]);
void delete_node(Node_ptr& a_list, char a_word[]);
void list_selection_sort(Node_ptr& a_list);
bool word_smaller(char* a, char*b);
void find_smallest(Node_ptr current_node, Node_ptr& smallest_node);
void swap(char a[], char b[]);

int main() {

  Node_ptr my_list = NULL;
  assign_list(my_list);

  cout << "The list is now:" << endl;
  print_list(my_list);
  cout << endl;

  char a_word[SIZE];
  char new_word[SIZE];
  cout << "After which word would you like to add an extra word?" << endl;
  cin >> a_word;
  cout << "Which word would you like to add?" << endl;
  cin >> new_word;
  add_after(my_list,a_word,new_word);
  cout << "The list is now:" << endl;
  print_list(my_list);
  cout << endl;

  char deletew[SIZE];
  cout << "Which word would you like to delete?" << endl;
  cin >> deletew;
  delete_node(my_list,deletew);
  cout << "The list is now:" << endl;
  print_list(my_list);
  cout << endl;

  list_selection_sort(my_list);
  cout << "After sorting, the list is: " << endl;
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

void add_after(Node_ptr& list, char a_word[], char word_after[]) {

  Node_ptr current_node, new_node;
  current_node = list;

  assign_new_node(new_node);
  strcpy(new_node->word,word_after);

  while (current_node != NULL) {
    if (!strcmp(a_word,current_node->word)) {
      new_node->ptr_next = current_node->ptr_next;
      current_node->ptr_next = new_node;
      return;
    }
  current_node = current_node->ptr_next;
  }

  delete new_node;
}

void delete_node(Node_ptr& a_list, char a_word[]) {

  Node_ptr node_before, current_node;
  current_node = a_list;
  node_before = a_list;

  while (current_node != NULL) {
    if (!strcmp(a_word,current_node->word)) {
      if (current_node == a_list)
	a_list = current_node->ptr_next;
      else
	node_before->ptr_next = current_node->ptr_next;
      delete current_node;
      return;
    }
    node_before = current_node;
    current_node = current_node->ptr_next;
  }
}

void list_selection_sort(Node_ptr& a_list) {

  Node_ptr current_node, small_node;
  current_node = a_list;

  while (current_node != NULL) {
    find_smallest(current_node,small_node);
    swap(current_node->word,small_node->word);
    current_node = current_node->ptr_next;
  }
}

void find_smallest(Node_ptr current_node, Node_ptr& smallest_node) {
  smallest_node = current_node;
  Node_ptr count = current_node->ptr_next;

  while (count != NULL) {
    if (word_smaller(count->word, smallest_node->word))
      smallest_node = count;
    count = count->ptr_next;
  }
}

bool word_smaller(char* a, char* b) {

  for (; (*a != '\0' && *b != '\0'); a++, b++) {
    if (*a > *b)
      return false;
    else if (*a < *b)
      return true;
  }
  if (*a == '\0' && *b == '\0')
    return true;
  else
    return false;

}

void swap(char a[], char b[]) {
  char temp[SIZE];
  strcpy(temp,a);
  strcpy(a,b);
  strcpy(b,temp);
}
