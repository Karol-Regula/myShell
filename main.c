#include <stdio.h>
#include <stdio.h>
#include "shellFnc.h"

int main(){
	char * input;
	char ** currentParsed;

	printf("\n");
	printf("Shell running...\n\n");

	while(1){//main loop for now
		input = getInput();

		currentParsed = parse(input);
		printInput(currentParsed);

		execute(currentParsed);
		printf("\n");
	}
}

//strlen to replace sizeof
//use malloc and define variables in the functions, dont do this stupid variable passing thing
