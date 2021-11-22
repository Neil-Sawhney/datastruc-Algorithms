#include <iostream>
using namespace std;

int main() {

	cout << "Hello World!\n";
	cout << "Hello World!" << "\n";

	try{
		while(true){cout<<".";cout.flush(); new char[100'000'000'00];}

	}
	catch(bad_alloc& b) {
		cerr << "Memory exhausted: " << b.what() << '\n';
	}

	return 0;
}
