#include <string>
#include <iostream>

using namespace std;

int main() {
	int original = 1;
	int newvariable = 2;
	int *pointer = &original;

	//Question Code goes here
	
	cout << (*pointer) << "\n";

	return 1;
}

