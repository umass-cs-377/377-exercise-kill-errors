# Exercise #6: Kill and Errors

## Overview

This exercise is designed to cover the [`kill`](https://man7.org/linux/man-pages/man2/kill.2.html) system call in C/C++, and to introduce some common errors and fixes that you may find useful in future projects. Please make sure that you do all your work in the Edlab environment, otherwise, there may be inconsistent results and you will not receive points. Please read through this exercise and follow the instructions. After you do that, visit Gradescope and complete the questions associated with this exercise by the assigned due date.

## Setup

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-exercise-kill-errors.git
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-exercise-kill-errors
```

This repo includes a `Makefile` that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.

## Part 1: Kill Command

Last week, we learned about various commands to create and wait for new processes. Many of these tasks are accomplished through the user of a process ID (typically referred to as a "pid"). Another use of a process ID is for the invoking the `kill` system call. As the name implies, this function _sends a signal_ to a process, some signals like `SIGQUIT1 will terminate the process immediately in the operating system[^1]. As an example, please look at the following code:

[^1]: More specifically, it removes it from the process list and deallocates all resources associated with it.

**`duality.cpp`**

```c++
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
```

**`kill.cpp`**

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

The code in `duality.cpp` creates two processes. The child process loops infinitely, printing out how many times it has looped so far. The parent process invokes fork, using the child process’ pid as the parameter. `Kill.cpp` simply invokes `kill` giving it the first command line argument passed to `main` and the [`SIGQUIT`](https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html#:~:text=The%20SIGQUIT%20signal%20is%20similar,%E2%80%9Cdetected%E2%80%9D%20by%20the%20user.) modifier which sends a quit signal to the process.

Note, we can use `kill` on the currently running process from within itself. While this is very similar to the `exit` function, it is not exactly the same, as the latter cleans up everything while closing and the former forcefully ends the task.

## Part 2: Segmentation Fault

Errors are a common issue when coding in any language, but are especially hard to solve in languages such as C/C++. The segmentation fault is one of the most common and unspecific errors in all of coding. Generally, the error stems from memory corruption, such as attempting to access memory that is not available to the program (i.e. read-only or free). When modifying values in C/C++, it is vital to ensure that you are not attempting to overwrite read-only data/code, nor are you trying to access code/data that is not available to your process. As an example, please look at the following code:

**`word.cpp`**

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

In this code, we assign a value to a char array, and then attempt to assign the value '3' to the address of `motto` plus 2. This results in a segmentation fault, since using \*(motto + 2) evaluates to a read-only location in memory. Accessing the location and printing it out will not give an error, but attempting to set its value results in a segmentation fault.

## Part 3: Debugging

Debugging errors is a necessary part of any coding process, such as determining what parts of code are causing which errors. However, with certain errors such as segmentation faults, it can be difficult to tell which parts of the code are causing errors. In these situations, tools like `gdb` are useful for finding what is going wrong. To use `gdb` on a program, use the command `gdb PROGRAM`, where PROGRAM is your program name (executable file). When using `gdb`, you can use the command `break LINENO`, where LINENO is a line number in the code to add a break. If you do so, a breakpoint will be placed at the specified line.

When you want to run your code in `gdb`, you can use the `run` command while `gdb` is active. If you do so, your code will pause at whatever place you put your breakpoints. Once at a breakpoint, we can either step into a function call using ‘step’ or ‘next’, with the latter stepping over functions. Additionally, in `gdb` you can print out the stack trace of the program (such as which methods have been run) by using the ‘bt’ command. When you are finished running `gdb`, use the ‘q’ command to exit the `gdb` interface.

A nice overview of using `gdb` can be found in [Dive Into Systems](https://diveintosystems.org/book/C3-C_debug/gdb.html) by Matthews, Newhall, and Webb. We recommend you take a look at it to get a better understanding of how to use `gdb`.

## Part 4: Code Review

We have covered how to fork child processes, wait until they complete, and execute new programs in place of child processes. The questions in Gradescope associated with this part examine your knowledge of putting these techniques together for a single program. Any imported assets should be assumed to already be included via the #include header. There is no definitive line limit, but points will be deducted for excessive lines of code.
