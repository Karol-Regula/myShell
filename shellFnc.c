#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shellFnc.h"

char * getInput(){//Obtains user input
	char * cmd = (char *) malloc(1000);
	printf("-----------------------------------------------------\n");
	printf("Enter a command: ");
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
	int front = 0;
	int end = 0;
	while(input[x]){
		front = 0;
		end = 0;
		printInput(&input[x]);
		if(x){
			front = 1;//To do: fix whitepsace processing
		}
		parse(input[x], front);
		x++;
	}
}

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
	printf("end: %d\n", end);
	if (input[end]){
			if (strcmp(input[end], "") == 0){
				printf("removed\n");
				input[end] = 0;
			}
	}

	input[x] = 0; //adding terminiating NULL to array

	printInput(input);
	execute(input);


//for redirection: find < or >, grab filenames on each side
}

void redirect(char ** input){
	printf("Redirecting... \n");
	int left;
	int right;
	char * fileName;
	int fd;

	left = find(input, "<");
	right = find(input, ">");
	printf("Index of left arrow: %d\n", left);
	printf("Index of right arrow: %d\n", right);

	//processing of right arrow, (output)
	if (right != -1){
		fileName = input[right + 1];
		fd = open(fileName, O_CREAT | O_EXCL | O_WRONLY | O_APPEND, 0664);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		input[right] = 0;
	}else{//processing of left arrow, (input)
		fileName = input[left - 1];
		fd = open(fileName, O_RDONLY, 0664);
		dup2(STDIN_FILENO, fd);
		close(fd);
		input[0] = input[left];
	}

	//executes program
	execvp(input[0], input);
	return;
}

void pipe(char ** input){
	
}

int find(char ** input, char * test){//finds string in array
	int x = 0;
	while(input[x]){
		if (! strcmp(input[x], test)){
			return x;
		}
		x++;
	}
	return -1;
}

void execute(char ** input){//executes program
	printf("Executing...\n\n");

	if(! strcmp(input[0], "exit")){//implementation of exit
		exit(0);
	}

	if (find(input, ">") != -1 || find(input, "<") != -1){
		redirect(input);
	}else{
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
}

void printInput(char ** input){//prints parsed command
	int x = 0;
	while(input[x]){
		printf("Input[%d] = %s\n", x, input[x]);
		x++;
	}
	return;
}

int countArgs(char ** input){
	int x = 0;
	while(input[x]){
		x++;
	}
	return x - 1;
}
