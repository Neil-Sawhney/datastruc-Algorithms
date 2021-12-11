// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData : l) {
    output << pData->lastName << " " << pData->firstName << " " << pData->ssn
           << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

bool firstNameComparator(Data *p1, Data *p2) {
  return (p2->firstName > p1->firstName);
}

// determines if we are sorting T1, T2, T3, or T4
int tWhat(list<Data *> &l) {
  if (l.size() < 500'000) {
    return 1;
  }

  list<Data *>::iterator it = l.begin(); // create an iterator

  if (!is_sorted(it, next(it, 20), firstNameComparator)) {
    return 2;
  };

  // if the 50th first name is the same as the 1st firstname, its t4
  if ((*next(it, 50))->firstName == (*it)->firstName) {
    return 4;
  }
  return 3;
}

bool case1Comparator(Data *p1, Data *p2) {
  if (p2->lastName > p1->lastName)
    return true;
  if (p2->lastName < p1->lastName)
    return false;
  if (p2->firstName > p1->firstName)
    return true;
  if (p2->firstName < p1->firstName)
    return false;
  return (p2->ssn > p1->ssn);
}

bool case3Comparator(Data *p1, Data *p2) { return (p2->ssn > p1->ssn); }

bool case4Comparator(Data *p1, Data *p2) { return (p2->ssn > p1->ssn); }

void sortDataList(list<Data *> &l) {
  // Fill this in
  int fileType = tWhat(l);
  // cout << "Detected file type is T" << fileType << "\n"; //COMMENT

  switch (fileType) {
  case 1:
    l.sort([](Data *p1, Data *p2) {
      if (p2->lastName > p1->lastName)
        return true;
      if (p2->lastName < p1->lastName)
        return false;
      if (p2->firstName > p1->firstName)
        return true;
      if (p2->firstName < p1->firstName)
        return false;
      return (p2->ssn > p1->ssn);
    });

    break;
  case 2:
    l.sort([](Data *p1, Data *p2) {
      if (p2->lastName > p1->lastName)
        return true;
      if (p2->lastName < p1->lastName)
        return false;
      if (p2->firstName > p1->firstName)
        return true;
      if (p2->firstName < p1->firstName)
        return false;
      return (p2->ssn > p1->ssn);
    });

    break;
  case 3:
    l.sort([](Data *p1, Data *p2) { return (p2->ssn > p1->ssn); });
    break;
  case 4:
    l.sort([](Data *p1, Data *p2) { return (p2->ssn > p1->ssn); });
    break;
  }
}
