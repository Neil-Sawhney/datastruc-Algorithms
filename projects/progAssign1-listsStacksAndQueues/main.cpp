#include <iostream>
#include <map>
#include <new>
#include <fstream>
#include <stdexcept>
#include <string>

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
    Node(Data DATA, Node *NEXT = nullptr) {
      data = DATA;
      next = NEXT;
    }
  };

private:
  // pointers to start and end of list
  Node *first = nullptr;
  Node *last = nullptr;

public:
  int size = 0;
  string listName;

  SimpleList(string LISTNAME = NULL) { this->listName = LISTNAME; }

  // function declaration and implementation beacause it's the same for both
  // stacks and queues
  Data pop() { return removeFromStart(); };
  // pure virtual push function because it differs for both stacks and queues
  virtual Data push(Data DATA) = 0;

  // a simple map to makes stream puts and error catching cleaner to implement
  static map<string, string> msg;

protected:
  // functions that manipulate nodes to be used for push and pop
  Data insertAtStart(Data DATA);
  Data insertAtEnd(Data DATA);
  Data removeFromStart();
};

// out of line definition of msg map
template <typename Data>
map<string, string> SimpleList<Data>::msg = {
    {"VAL_POP", "Value popped: \n"},
    {"ERROR_EMPTY", "ERROR: This list is empty!\n"},
    {"ERROR_DNE", "ERROR: This name does not exist!\n"},
};

// A Templated Function that inserts a node at the start of the list
// returns the value pushed
template <typename Data> Data SimpleList<Data>::insertAtStart(Data DATA) {
  // point our new node to the lists previous first node
  Node *NEXT = first;
  Node *node = new Node(DATA, NEXT);
  // tell SimpleList that the lists first node is now our new node
  first = node;
  if (size == 0)
    last = first;
  size++;
  return (DATA);
}

// A Templated Function that inserts a node at the end of the list
// returns the value popped
template <typename Data> Data SimpleList<Data>::insertAtEnd(Data DATA) {
  if (size == 0)
    insertAtStart(DATA);
  else {
    // point the lists last node to our new node
    Node *node = new Node(DATA);
    last->next = node;
    // tell SimpleList that the lists last node is now our new node
    last = node;
    size++;
  }
  return (DATA);
}

// A Templated Function that removes a node at the start of the list
// returns the data removed, or NULL if passed an empty list
template <typename Data> Data SimpleList<Data>::removeFromStart() {
  Node *tmp = first;
  // empty list
  if (size == 0)
    throw invalid_argument("ERROR_EMPTY");
  // tell SimpleList that the list's first node is the second node
  first = first->next;
  Data removedData = tmp->data;
  delete tmp;
  size--;
  return removedData;
}

// A Templated Stack Class That Inherits SimpleList
// Pushes to start and pops from start
template <typename Data> class Stack : public SimpleList<Data> {
public:
  using SimpleList<Data>::SimpleList;
  Data push(Data DATA) { return this->insertAtStart(DATA); };
};

// A Templated Queue Class That Inherits SimpleList
// Pushes to end and pops from start
template <typename Data> class Queue : public SimpleList<Data> {
public:
  using SimpleList<Data>::SimpleList;
  Data push(Data DATA) { return this->insertAtEnd(DATA); };
};

//requests the user for an input name and opens the file
void openInputFile(){
  string inputFile;
  cin >> inputFile;
  ifstream input(inputFile);
}

//requests the user for an output name and opens the file
void openOutputFile(){
  string outputFile;
  cin >> outputFile;
  ofstream output(outputFile);
}

// Parse input file, put the appropriate commands to the output file
void handler() {

  SimpleList<int> *L1 = new Queue<int>("L1");

  try {
    cout << "pushed: " << L1->push(1) << "\n";
    cout << "pushed: " << L1->push(2) << "\n";
    cout << "pushed: " << L1->push(3) << "\n";
    cout << "pushed: " << L1->push(4) << "\n";

    cout << "popped: " << L1->pop() << "\n";
    cout << "popped: " << L1->pop() << "\n";
    cout << "popped: " << L1->pop() << "\n";
    cout << "popped: " << L1->pop() << "\n";
    cout << "popped: " << L1->pop() << "\n";
  } catch (const invalid_argument &e) {
    cout << SimpleList<int>::msg[e.what()];
  }
}

int main() {
  openInputFile();
  openOutputFile();
  handler();
};