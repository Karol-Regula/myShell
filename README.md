Shell
by Karol Regula

##Features:
	Clear user interface and responsive messages.
	Accepts multiple commands on a single line, delimited with ';'.
	Supports redirecting using '<' and '>'.
	"exit" command causes shell to exit.
	Supports piping using a single '|'.

##Attempted:
	The following did not end up working, but have been left in the code, commented out.
	Tried to implement white space removal.
	Tried to implement >>, but it kept overwriting the file
	Looked at replacing ~/ with home directory, got seg faults.

##Bugs / Features:
	Not necessarily bug: All arguments must be separated with a space and made within reason, shell does not support Star Wars playback.
	Only a single '>', '<', '|' may be used at a time.

##Files & Function Headers:

###main.c
	Handles main loop and some input retrieval.

	/*======== int main() ==========
	Inputs: None
	Returns: int

	Contains main loop that always runs while the shell is active.
	Exits with exit(0) when "exit" is typed into shell.
	Plays a small role in passing input strings in between functions.
	====================*/

###parse.c
	Handles both string parsing functions.

	/*======== void parseLine() ==========
	Inputs: char * cmd
	Returns: void

	Separates string into array of pointers using ';' as a delimiter.
	Does some basic whitespace avoidance operations.
	====================*/

	/*======== void parseLine() ==========
	Inputs: char * cmd
			int front
	Returns: void

	Separates string into array of pointers using ' ' as a delimiter.
	Does some basic whitespace avoidance operations.
	int front is used to determine if whitespace after a ';' is to be ignored.
	====================*/

###shellFnc.c
	Handles main features such as execution, redirecting and piping. Also contains helper functions.

	/*======== char * getInput() ==========
	Inputs: None
	Returns: char *

	Uses fgets() to obtain use input from commandline.
	Removes newline character from input.
	Passes input back to main() as a string.
	====================*/

	/*======== void redirect() ==========
	Inputs: char ** input
	Returns: void

	Identifies location of redirection operators in the expression.
	Cuts up inputted commands and open / reads from files as needed.
	Uses dup2() to manage file descriptors.
	====================*/

	/*======== void piper() ==========
	Inputs: char ** input
	Returns: void

	Identifies location of pipe in expression.
	Creates copies of 2 main file descriptors.
	Opens pipe, forks two children and pipes data.
	====================*/

	/*======== int find() ==========
	Inputs: char ** input
			char * test
	Returns: int

	char ** input is target array of pointers.
	char * test is character that is looked for.
	Returns location of test in input.
	If not found, returns -1.
	====================*/

	/*======== void execute() ==========
	Inputs: char ** input
	Returns: void

	Takes parsed command from ' ' delimiter parser.
	Checks for exit commands, change of directory, redirection, or pipe.
	Calls appropriate function or executes command itself if no special requirement is needed.
	====================*/

	/*======== void printInput() ==========
	Inputs: char ** input
	Returns: void

	Accepts array of pointers.
	Prints the array of pointers in a nicely formatted way.
	====================*/

	/*======== int countArgs() ==========
	Inputs: char ** input
	Returns: int

	Counts number of arguments in array of pointers.
	Returns that number.
	====================*/
