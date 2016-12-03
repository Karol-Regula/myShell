#include <stdio.h>
#include <stdio.h>
#include "shellFnc.h"
#include "parse.h"


/*======== int main() ==========
Inputs:  None
Returns: int

Contains main loop that always runs while the shell is active.
Exits with exit(0) when "exit" is typed into shell.
Plays a small role in passing input strings in between functions.
====================*/
int main(){
	char * input;

	printf("\n");
	printf("Please separate each argument with one space.\n");
	printf("Shell running...\n\n");

	while(1){//main loop for now
		input = getInput();

		parseLine(input);

		printf("\n");
	}
}

//use malloc and define variables in the functions, dont do this stupid variable passing thing
