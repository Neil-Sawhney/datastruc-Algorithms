#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// template stuff
template <typename Data>
void print(Data dog) { cout << dog; }


//pointer stuff
/*
	a pointer is just the address.
	*variable derefrences and accesesses the value.
	int* blah = variable, creates a pointer to the address of variable 
*/

//defining a reference to the varibale passed in, and naming it fingie.
void pointer(int& fingie)
{
 fingie++; 
}

int main() {

  /*
    //echo some input
    string hello = "";
    cout << "You have entered a cave...\n";
    cin >> hello;
    cout << hello << "\n";
   */

  /*
   cout << "you've encountered a bear, give it a file\n";
   // ask the user for a file name
   string inputFile;
   cin >> inputFile;
   ifstream input(inputFile);
   */

  /*
  // print every line in file "commands1.txt" and paste into a new file
  string s;
  ifstream input("commands1.txt");
  ofstream output("cTestsOutput.txt");
  while (getline(input, s)) {
    cout << s << "\n";
    output << s << "\n";
  }

  //close the files
  input.close();
  output.close();
*/

/*
  //printing template stuff 
  int cat = 5;
  string bat = "kacka";
  print(cat);
  print(bat);
*/

  /*
  //pointer stuff
  int cat = 5;
  int *bat = &cat;
  int &kangaroo = cat;
  print(cat);
  print(kangaroo);
  cout << "\n";
  print(bat);
  cout << "\n";
  //pass to pointer to increment it then print again
  pointer(cat);
  print(cat);
  print(kangaroo);
  */

  return 0;
}
