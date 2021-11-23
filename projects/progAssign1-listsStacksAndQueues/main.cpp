#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

// An Abstract Base Class called SimpleList:
template <typename Data> class SimpleList {
private:
  // A Private Nested Class Called Node:
  class Node {
  public:
    Data data;
    Node *next;

    // constructor for Node
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

  // constructor for SimpleList
  SimpleList(string LISTNAME = NULL) { this->listName = LISTNAME; }

  // function declaration and implementation beacause it's the same for both
  // stacks and queues
  Data pop() { return removeFromStart(); };
  // pure virtual push function because it differs for both stacks and queues
  virtual Data push(Data DATA) = 0;

protected:
  // functions that manipulate nodes to be used for push and pop
  Data insertAtStart(Data DATA);
  Data insertAtEnd(Data DATA);
  Data removeFromStart();
};

// A Function that inserts a node at the start of the list
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

// Inserts a node at the end of the list
// Returns the value popped
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

// Removes a node at the start of the list
// returns the data removed, or throws an error if passed an empty list
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

// A Stack Class That Inherits SimpleList
// Pushes to start and pops from start
template <typename Data> class Stack : public SimpleList<Data> {
public:
  using SimpleList<Data>::SimpleList;
  Data push(Data DATA) { return this->insertAtStart(DATA); };
};

// A Queue Class That Inherits SimpleList
// Pushes to end and pops from start
template <typename Data> class Queue : public SimpleList<Data> {
public:
  using SimpleList<Data>::SimpleList;
  Data push(Data DATA) { return this->insertAtEnd(DATA); };
};

// A map to make stream puts and error catching less messy to remember
map<string, string> msg = {
    {"INPUT", "Enter name of input file: "},
    {"OUTPUT", "Enter name of output file: "},
    {"PROCESS", "PROCESSING COMMAND: "},
    {"VAL_POP", "Value popped: "},
    {"ERROR_EMPTY", "\nERROR: This list is empty!"},
    {"ERROR_DNE", "\nERROR: This name does not exist!"},
    {"ERROR_AE", "\nERROR: This name already exists!"},
};

// requests the user for an input name and opens the file
ifstream openInputFile() {
  string inputFile;
  cout << msg["INPUT"];
  cin >> inputFile;
  ifstream INPUT(inputFile);
  return INPUT;
}

// requests the user for an output name and opens the file
ofstream openOutputFile() {
  string outputFile;
  cout << msg["OUTPUT"];
  cin >> outputFile;
  ofstream OUTPUT(outputFile);
  return OUTPUT;
}

list<SimpleList<int> *> listSLi;    // all integer stacks and queues
list<SimpleList<double> *> listSLd; // all double stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues

// Takes a list name as a parameter and uses it to find the simple list with
// that name in the list of simple lists for the appropriate dataType
template <typename Data>
_List_iterator<SimpleList<Data> *> findSimpleList(string LIST_NAME) {
  return find_if(
      listSLi.begin(), listSLi.end(),
      [&](SimpleList<int> *const &p) { return p->listName == LIST_NAME; });
}
// these are almost the same, but for different datatypes
template <>
_List_iterator<SimpleList<double> *> findSimpleList(string LIST_NAME) {
  return find_if(
      listSLd.begin(), listSLd.end(),
      [&](SimpleList<double> *const &p) { return p->listName == LIST_NAME; });
}
template <>
_List_iterator<SimpleList<string> *> findSimpleList(string LIST_NAME) {
  return find_if(
      listSLs.begin(), listSLs.end(),
      [&](SimpleList<string> *const &p) { return p->listName == LIST_NAME; });
}

// create an integer stack or queue and add it do the list
void create(string DATA_TYPE, string INGREDIENTS, string LIST_NAME) {
  if (DATA_TYPE == "i") {
    // if a list with that name exists throw an error
    if (findSimpleList<int>(LIST_NAME) != listSLi.end())
      throw invalid_argument("ERROR_AE");

    SimpleList<int> *SLi;
    if (INGREDIENTS == "queue")
      SLi = new Queue<int>(LIST_NAME); // create a new queue
    else
      SLi = new Stack<int>(LIST_NAME); // create a new stack
    listSLi.push_front(SLi);           // add it to the list
  }

  else if (DATA_TYPE == "d") {
    // if a list with that name exists throw an error
    if (findSimpleList<double>(LIST_NAME) != listSLd.end())
      throw invalid_argument("ERROR_AE");

    SimpleList<double> *SLd;
    if (INGREDIENTS == "queue")
      SLd = new Queue<double>(LIST_NAME); // create a new queue
    else
      SLd = new Stack<double>(LIST_NAME); // create a new stack
    listSLd.push_front(SLd);              // add it to the list
  }

  else if (DATA_TYPE == "s") {
    // if a list with that name exists throw an error
    if (findSimpleList<string>(LIST_NAME) != listSLs.end())
      throw invalid_argument("ERROR_AE");

    SimpleList<string> *SLs;
    if (INGREDIENTS == "queue")
      SLs = new Queue<string>(LIST_NAME); // create a new queue
    else
      SLs = new Stack<string>(LIST_NAME); // create a new stack
    listSLs.push_front(SLs);              // add it to the list
  }
}

// push a value to a SimpleList
void push(string DATA_TYPE, string INGREDIENTS, string LIST_NAME) {
  if (DATA_TYPE == "i") {
    _List_iterator<SimpleList<int> *> listCandidate = findSimpleList<int>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (listCandidate == listSLi.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<int> * FoundList = *listCandidate;
    FoundList->push(stoi(INGREDIENTS));
  }

  else if (DATA_TYPE == "d") {
    _List_iterator<SimpleList<double> *> listCandidate = findSimpleList<double>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (findSimpleList<double>(LIST_NAME) == listSLd.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<double> * FoundList = *listCandidate;
    FoundList->push(stod(INGREDIENTS));
  }

  else if (DATA_TYPE == "s") {
    _List_iterator<SimpleList<string> *> listCandidate = findSimpleList<string>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (findSimpleList<string>(LIST_NAME) == listSLs.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<string> * FoundList = *listCandidate;
    FoundList->push(INGREDIENTS);
  }
}

// pop a value from a SimpleList
string pop(string DATA_TYPE, string INGREDIENTS, string LIST_NAME) {
  if (DATA_TYPE == "i") {
    _List_iterator<SimpleList<int> *> listCandidate = findSimpleList<int>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (listCandidate == listSLi.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<int> * FoundList = *listCandidate;
    return to_string(FoundList->pop());
  }

  else if (DATA_TYPE == "d") {
    _List_iterator<SimpleList<double> *> listCandidate = findSimpleList<double>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (findSimpleList<double>(LIST_NAME) == listSLd.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<double> * FoundList = *listCandidate;

    string str = to_string(FoundList->pop());
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    return str;
  }

  else if (DATA_TYPE == "s") {
    _List_iterator<SimpleList<string> *> listCandidate = findSimpleList<string>(LIST_NAME);
    // if a list with that name does not exist throw an error
    if (findSimpleList<string>(LIST_NAME) == listSLs.end())
      throw invalid_argument("ERROR_DNE");
    SimpleList<string> * FoundList = *listCandidate;
    return FoundList->pop();
  }
  return "";
}

// Parse input file, put the appropriate commands to the output file
void parse() {
  ifstream input = openInputFile();
  ofstream output = openOutputFile();

  string cLine;
  //to skip the first run through of outputting a new line
  bool toggle = false;
  // Grab one line at a time until we've ran every command
  while (getline(input, cLine)) {
    //new line at the top to stop the end of file new line
    if (toggle) {
      output << "\n";
    }
    toggle = true;

    // processing command
    output << msg["PROCESS"] << cLine;

    // Chop that line up into words and toss them into a vector
    istringstream iss(cLine);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    string listName = tokens.at(1);
    string dataType =
        listName.substr(0, 1);     // dataType is the first char in name
    string command = tokens.at(0); // create, push, or pop
    string ingredients =
        (command == "pop") ? "" : tokens.at(2); //"stack" or "queue" for create.
                                                // value for push. Null for pop

    //proccess all commands, and catch any errors in the proccess
    try {
      if (command == "create") {
        create(dataType, ingredients, listName);
      }
      else if (command == "push") {
        push(dataType, ingredients, listName);
      }
      else if (command == "pop") {
        string popVal = pop(dataType, ingredients, listName) ;
        output << "\n" << msg["VAL_POP"] << popVal;
      }

    } catch (const invalid_argument &e) {
      output << msg[e.what()];
    }
  }
}

int main() { parse(); };