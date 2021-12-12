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

// Function that performs Radix Sort
void radix_sort(list<Data *> l) {

  // create a vector of ssn's
  int arr[l.size()];

// create a list of all ssns
  auto it = l.begin();
  stringstream happystream;
  string happyoutput;
  for (int i = 0; i < l.size(); ++i) {
    happyoutput = (*it)->ssn;
    happyoutput.erase(3,1);
    happyoutput.erase(5,1);
    happystream << happyoutput;
    int temp;
    happystream >> temp;
    arr[i] = temp;
    advance(it,1);
    happystream.clear();
  }

  int digits = 9;
  int n = l.size();

  // Step 3, 4, 5: Arrange the numbers on the basis of digits
  for (int i = 0; i < digits; i++) {

    // Units/Tens/Hundreds - used to determine which digit
    int power = pow(10, i);

    // Holds the updated array
    int new_array[n];

    // Counting Sort Array - required for arranging digits [0-9]
    int count[10];

    // Initializing Count Array
    memset(count, 0, sizeof(count));

    // Calculating frequency of digits
    for (int j = 0; j < n; j++) {

      // The digit under consideration in this iteration
      int num = (arr[j] / power) % 10;

      count[num]++;
    }

    // Cumulative frequency of count array
    for (int j = 1; j < 10; j++) {
      count[j] += count[j - 1];
    }

    // Designating new positions in the updated array
    for (int j = n - 1; j >= 0; j--) {

      // The digit under consideration in this iteration
      int num = (arr[j] / power) % 10;

      new_array[count[num] - 1] = arr[j];
      count[num]--;
    }
    // Printing the unsorted array
    for(int j=0;j<10;j++)
        cout<<arr[j]<<" ";
 
    cout<<endl;
    // Printing the sorted array
    for(int j=0;j<10;j++)
        cout<<new_array[j]<<" ";
 
    cout<<endl;

    // Updating the list using New Array
    int j = 0;
    for (auto it : l) {
    it->ssn = new_array[j];
    j++;
    }
  }
}

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
    radix_sort(l);
    break;
  }
}
