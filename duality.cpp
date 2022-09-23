#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
	int pid = fork();
	if (pid == 0){
		int runs = 0;
		while (runs < 10000){
			runs += 1;
			std::cout << "Run #" << runs << "\n";
                        std::this_thread::sleep_for (std::chrono::milliseconds(1));
		}
	} else {
		char test[3];
		sprintf(test, "%d", pid);
	
		char *arguments[4];
		arguments[0] = (char*)"./kill";
		arguments[1] = strdup(test);
		arguments[2] = NULL;
                arguments[3] = NULL;

		//Question code goes here
	
		std::cout << "finish them?\n";
		execvp(arguments[0], arguments);
	}
}	

```	
