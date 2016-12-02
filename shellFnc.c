#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shellFnc.h"

char * getInput(){//Obtains user input
	char * cmd = (char *) malloc(1000);
	printf("---------------------------Enter a command: ");
	fgets(cmd, 1000, stdin); //sizeof does not work
	char * r = strchr(cmd, '\n');//strchr returns pointer, set to zero to remove /n
	*r = 0;
	//printf("%s\n", cmd);
	return cmd;
}

void parseLine(char * cmd){
	printf("Full Input: %s\n", cmd);
	char ** input = (char **) malloc(1000);
	char * s = cmd;
	int x = 0;
	while (s){
		input[x] = strsep(&s, ";"); //parsing / separating command
		x++;
	}
	input[x] = 0;
	x = 0;
	int n = 0;
	while(input[x]){
		printInput(&input[x]);
		if(x){
			n = 1;//To do: fix whitepsace processing
		}
		parse(input[x], n);
		x++;
	}
}

void parse(char * cmd, int n){//Parses and prepares user input
	char ** input = (char **) malloc(1000);
	char * s = cmd;
	int x = 0;
	while (s){
		input[x] = strsep(&s, " "); //parsing / separating command
		x++;
	}
	input[x] = 0; //adding terminiating NULL to array

	printInput(&input[n]);
	execute(&input[n]);

}

void execute(char ** input){//executes program
	printf("Executing...\n\n");

	if(! strcmp(input[0], "exit")){//implementation of exit
		exit(0);
	}

	if(strcmp(input[0], "cd") == 0){//implementation of redirection
		chdir(input[1]);
	}else{
		int pid = fork();
		if (pid == 0){
			execvp(input[0], input);
		}else{
			wait(&pid);
		}
	}
}

void printInput(char ** input){//prints parsed command
	int x = 0;
	while(input[x]){
		printf("Input[%d] = %s\n", x, input[x]);
		x++;
	}
	return;
}
