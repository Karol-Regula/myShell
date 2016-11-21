#include <stdio.h>
#include <stdio.h>
#include "shellFnc.h"

int main(){
	char current[100];
	char * currentParsed[20];

	printf("\n");
	printf("Shell running...\n");
	current[0] = readInput();
	currentParsed[0] = parse(current);
	printInput(currentParsed);
	execute(currentParsed);
	printf("\n");
	return 0;
}
