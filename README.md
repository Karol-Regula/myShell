Shell
by Karol Regula

Features:
	Clear user interface and responsive messages.
	Accepts multiple commands on a single line, delimited with ';'.
	Supports redirecting using '<' and '>'.
	Supports piping using a single '|'.

Attempted:
	The following did not end up working, but have been left in the code, commented out.
	Tried to implement white space removal.
	Tried to implement >>, but it kept overwriting the file
	Looked at replacing ~/ with home directory, got seg faults.

Bugs / Features:
	Not necessarily bug: All arguments must be separated with a space and made within reason, shell does not support Star Wars playback.
	Only a single '>', '<', '|' may be used at a time.

Files & Function Headers:
shell.c
	Handles shell backend functions
	/*======== int count_tokens() ==========
	Inputs:  char *line
        	  char delim
	Returns: Number of tokens in line separated by delim

	Counts the number of times the character delim appears in the
	 string line
	The number of tokens is 1 more than the number of appearences
	of delim
	If delim does not appear, 1 is returned
	====================*/

	/*======== char ** parse_line() ==========
	Inputs:  char *line
	Returns: Array of strings where each entry is a token
	separated by delim

	If line contains multiple tokens separated by delim, this
	function will put each token into an array of strings
	====================*/

	/*======== char * trim() ==========
	Inputs:  char *line
	Returns: Pointer to the beginning of line

	Removes leading and trailing whitespace on the string line.
	Terminating '\0' is placed at a new location if necessary.
	====================*/

main.c
	Handles main loop and some input retrieval.
