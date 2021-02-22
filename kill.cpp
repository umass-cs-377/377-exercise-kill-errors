#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <signal.h>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "finish them.\n";
	kill(atoi(argv[1]), SIGQUIT);	
}
