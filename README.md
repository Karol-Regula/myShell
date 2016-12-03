Shell
by Karol Regula

##Features:
	Clear user interface and responsive messages.
	Accepts multiple commands on a single line, delimited with ';'.
	Supports redirecting using '<' and '>'.
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
###parse.c
	Handles both string parsing functions.

	/*======== void parseLine() ==========
	Inputs:  char * cmd
	Returns: void

	Separates string into array of pointers using ';' as a delimiter.
	Does some basic whitespace avoidance operations.
	====================*/

	/*======== void parseLine() ==========
	Inputs:  char * cmd
			 int front
	Returns: void

	Separates string into array of pointers using ' ' as a delimiter.
	Does some basic whitespace avoidance operations.
	int front is used to determine if whitespace after a ';' is to be ignored.
	====================*/



###main.c
	Handles main loop and some input retrieval.

	/*======== int main() ==========
	Inputs:  None
	Returns: int

	Contains main loop that always runs while the shell is active.
	Exits with exit(0) when "exit" is typed into shell.
	Plays a small role in passing input strings in between functions.
	====================*/
