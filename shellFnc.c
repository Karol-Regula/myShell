#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char * getInput(){//Obtains user input
	char * cmd = (char *) malloc(1000);
	printf("command: %s\n", cmd);
	printf("Enter a command:");
	fgets(cmd, sizeof(cmd), stdin); //sizeof works correctly
	char * r = strchr(cmd, '\n');//strchr returns pointer, set to zero to remove /n
	r = NULL;
	//printf("%s\n", cmd);
	return cmd;
}

char * parse(char command){//Parses and prepares user input
	char * input[20];
	char * s = &command;
	char * p = &command;
	int x = 0;
	while (s){
		input[x] = strsep(&s, " "); //parsing / separating command
		x++;
	}
	input[x] = NULL; //adding terminiating NULL to array
	return input[0];
}

//may be able to get rid of stars and &
int execute(char * input){//executes program, does not fork yet
	printf("Executing\n");
	execvp(&input[0], &input); //executing command
	return 0;
}

void printInput(char * input){
	int x = 0;
	while(&input[x]){
		printf("Input[%d] = %s", x, &input[x]);
		x++;
	}
}
