#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

  // print every line in file "commands1.txt" and paste into a new file called "cTestsOutput.txt"

  ifstream input("commands1.txt");
  ofstream output("cTestsOutput.txt");

  string s;
  while (getline(input, s)) {
    cout << s << "\n";
    output << s << "\n";
  }
  input.close();
  output.close();


  return 0;
}
