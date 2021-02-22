#include <string>
#include <iostream>

using namespace std;

int main() {
	char *motto; 
   	motto = "CS477iscool";   
   	*(motto + 2) = '3'; 
	return 0;
}
