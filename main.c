#include <stdio.h>
#include <stdio.h>
#include "shellFnc.h"

int main(){
	char * input;
	char current[100];
	char * currentParsed[20];

	printf("\n");
	printf("Shell running...\n\n");
	input = getInput();
	printf("Input: %s\n", input);
	//currentParsed[0] = parse(current);
	//printInput(currentParsed);
	//execute(currentParsed);
	printf("\n");
	return 0;
}

//strlen to replace sizeof
//use malloc and define variables in the functions, dont do this stupid variable passing thing
