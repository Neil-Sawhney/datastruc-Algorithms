#include <iostream>

using namespace std;

// An Abstract Templated SimpleList Base Class:
template <typename Data> class SimpleList {
private:
  // A Private Nested Class Called Node:
  class Node {
  public:
    Data data;
    Node *next;

    // constructor for Node accepts data and pointer, if no pointer is provided
    // it is defaulted to NULL
    Node(Data DATA, Node *NEXT = NULL) {
      data = DATA;
      next = NEXT;
    }
  };

private:
  Node *first; // first node of the list
  Node *last;  // last node of the list
public:
  int size; // size of the list
  SimpleList() {
    first, last, size = NULL, NULL, 0;
  } // constructor for SimpleList
protected:
  virtual void push(Data DATA) = 0; // pure virtual function declarations to insert node at start or end, must be overridden by stacks and queues
  Data pop(); // function declaration to remove node from the start, used for both stacks and queues
};

int main(){

};