#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char readInput(){//Obtains user input
	char cmd[100];
	char cmdNew[100];
	printf("Enter a command: \n");
	fgets(cmd, sizeof(cmd) , stdin);
	strncpy(cmdNew, cmd, strlen(cmd) - 1); //fixing fgets input
	//printf("%s\n", cmd);
	return cmdNew[0];
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
