# COMPSCI 377 LAB #3: Kill and Errors

## Purpose

This lab is designed to cover the kill() command in C++, and to introduce some common errors and fixes that you may find useful in future projects. Please make sure that all of your answers to questions in these labs come from work done on the Edlab environment – otherwise, they may be inconsistent results and will not receive points.

Please submit your answers to this lab on Gradescope in the assignment marked “Lab #3’. All answers are due by the time specified on Gradescope. The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by yourself. Please raise your hand if you have any questions during the lab section – TAs will be notified you are asking a question. Questions and Parts have a number of points marked next to them to signify their weight in this lab’s final grade. Labs are weighted equally, regardless of their total points.

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-lab-kill-errors.git
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-lab-kill-errors
```

This repo includes a Makefile that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.

## Part 1: Kill Command (6 Points)

Last week, we learned about various commands to create and wait for new processes. Many of these tasks are accomplished through the user of a Process ID. Another use of a Process ID is for the kill() command. As the name implies, this function kills a process, making it end immediately on the operating system. As an example, please look at the following code:

duality.cpp
```c++
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
		arguments[0] = (char*)"./fork";
		arguments[1] = strdup(test);
		arguments[2] = NULL;

		//Question code goes here
		int pid2 = fork();
	
		std::cout << "finish them?\n";
		execvp(arguments[0], arguments);
	}
}
```

kill.cpp
```c++
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
```

The code in duality.cpp creates two processes. The child process loops infinitely, printing out how many times it has looped so far. The parent process runs fork, using the child process’ pid as the parameter. Kill.cpp simply runs kill on the first argument it receives, with the SIGQUIT modifier to send a quit message to the process.

Additionally, we can use kill() on the currently running process from itself. While this is very similar to the exit() function, it is not exactly the same, as the latter cleans up everything while closing and the former forcefully ends the task.

## Part 2: Segmentation Fault (5 Points)

Errors are a common issue when coding in various languages, but are especially hard to solve sometimes in languages such as C++. The segmentation fault is one of the most common and unspecific errors in all of coding. Generally, the error stems from memory corruption, such as attempting to access memory that is not available to the program (i.e. read-only or free). When modifying values in C++, it is vital to ensure that you are not attempting to overwrite read-only information, nor are you trying to access information that is not available to your code. As an example, please look at the following code:

word.cpp
```c++
#include <string>
#include <iostream>

using namespace std;

int main() {
	char *motto; 
  motto = "CS477iscool";     
  *(motto + 2) = '3';
  
  return 1;
}
```

In this code, we assign a value to a char array, and then attempt to assign the value located at the address plus 2 to ‘3’. This gives a segmentation fault, since using \*(motto + 2) returns a read-only piece of information. Printing it out will not give an error, but attempting to set its value ends up causing a Segmentation fault because of it.

## Part 3: Debugging (2 Points)

Debugging errors is a necessary part of any coding process, such as determining what parts of a code are causing which errors. However, with certain errors such as Segmentation faults, it can be difficult to tell which parts of the code are causing errors. In these situations, tools like gdb are useful for finding what is going wrong. To use gdb on a program, use the command ‘gdb \_\_\_\_’, where the blank space is your program name. When using gdb, you can use the command ‘gdb \_\_\_’, where the blank space is a line in the code. If you do so, there is a breakpoint placed at the line specified.

When you want to run your code in gdb, you can use the run command while gdb is active. If you do so, your code will pause at whatever place you put your breakpoints. Once at a breakpoint, we can either step into a function call using ‘step’ or ‘next’, with the latter stepping over functions. Additionally, in gdb you can print out the stack trace of the program (such as which methods have been run) by using the ‘bt’ command. When you are finished running gdb, use the ‘q’ command to exit the gdb interface. An example of gdb will be shown in the live lab session.

## Part 4: Code Review (8 Points)

The past 3 labs have covered various techniques for coding using processes and executables in C++. The following questions examine your knowledge of putting these techniques together for a single program. Any imported assets should be assumed to already be included via the #include header. There is no definitive line limit, but points will be deducted for excessive lines of code.
