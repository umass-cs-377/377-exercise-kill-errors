#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

int main() {
	int pid = fork();
	if (pid == 0){
		int runs = 0;
		while (true){
			runs += 1;
			std::cout << "Run #" << runs << "\n";
		}
	} else {
		char test[3];
		sprintf(test, "%d", pid);
	
		char *arguments[3];
		arguments[0] = (char*)"./kill";
		arguments[1] = strdup(test);
		arguments[2] = NULL;

		//Question code goes here
	
		std::cout << "finish them?\n";
		execvp(arguments[0], arguments);
	}
}	
