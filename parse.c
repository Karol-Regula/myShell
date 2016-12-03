#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"
#include "shellFnc.h"


/*======== int parseLine() ==========
Inputs: char * cmd
Returns: void

Separates string into array of pointers using " " as a delimiter.
Does some basic whitespace avoidance operations.
====================*/
void parseLine(char * cmd){
	//printf("Full Input: %s\n", cmd);
	char ** input = (char **) malloc(1000);
	char * s = cmd;
	int x = 0;
	while (s){
		input[x] = strsep(&s, ";"); //parsing / separating command
		x++;
	}
	input[x] = 0;
	x = 0;
	int front = 0;
	int end = 0;
	while(input[x]){
		front = 0;
		end = 0;
		//printInput(&input[x]);
		if(x){
			front = 1;//To do: fix whitepsace processing
		}
		parse(input[x], front);
		x++;
	}
}

/*======== void parseLine() ==========
Inputs: char * cmd
		int front
Returns: void

Separates string into array of pointers using ' ' as a delimiter.
Does some basic whitespace avoidance operations.
int front is used to determine if whitespace after a ';' is to be ignored.
====================*/
void parse(char * cmd, int front){//Parses and prepares user input
	char ** input = (char **) malloc(1000);
	char * s = cmd;
	int x = 0;
	int end = 0;
	while (s){
		input[x] = strsep(&s, " "); //parsing / separating command
		x++;
	}

	input = &input[front];

	end = countArgs(&input[0]);//whitespace
	//printf("end: %d\n", end);
	if (input[end]){
			if (strcmp(input[end], "") == 0){
				//printf("removed\n");
				input[end] = 0;
			}
	}

	input[x] = 0; //adding terminiating NULL to array

	//printInput(input);
	execute(input);


//for redirection: find < or >, grab filenames on each side
}
