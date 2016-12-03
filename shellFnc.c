#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shellFnc.h"
#include "parse.h"

/*======== char * getInput() ==========
Inputs: None
Returns: char *

Uses fgets() to obtain use input from commandline.
Removes newline character from input.
Passes input back to main() as a string.
====================*/
char * getInput(){//Obtains user input
	char * cmd = (char *) malloc(1000);
	printf("-----------------------------------------------------\n");
	printf("Enter a command $ ");
	fgets(cmd, 1000, stdin); //sizeof does not work
	char * r = strchr(cmd, '\n');//strchr returns pointer, set to zero to remove /n
	*r = 0;
	//printf("%s\n", cmd);
	return cmd;
}

/*======== void redirect() ==========
Inputs: char ** input
Returns: void

Identifies location of redirection operators in the expression.
Cuts up inputted commands and open / reads from files as needed.
Uses dup2() to manage file descriptors.
====================*/
void redirect(char ** input){
	printf("Redirecting... \n");
	int left;
	int right;
	char * fileName;
	int fd;

	left = find(input, "<");
	right = find(input, ">");
	int STDOUT_FILENOx = dup(STDOUT_FILENO);
	int STDIN_FILENOx = dup(STDIN_FILENO);
	//printf("Index of left arrow: %d\n", left);
	//printf("Index of right arrow: %d\n", right);

	//processing of right arrow, (output)
	if (right != -1){
		fileName = input[right + 1];
		fd = open(fileName, O_CREAT | O_WRONLY | O_APPEND, 0664);
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
	int pid = fork();
	if (pid == 0){
		execvp(input[0], input);
	}else{
		wait(&pid);
	}
	dup2(STDOUT_FILENOx, STDOUT_FILENO);
	close(STDOUT_FILENOx);
	dup2(STDIN_FILENOx, STDIN_FILENO);
	close(STDIN_FILENOx);
	printf("\n");
	return;
}

/*======== void piper() ==========
Inputs: char ** input
Returns: void

Identifies location of pipe in expression.
Creates copies of 2 main file descriptors.
Opens pipe, forks two children and pipes data.
====================*/
void piper(char ** input){
	printf("Piping... \n");
	int index = find(input, "|");
	int pid = 0;
	int pid2 = 0;
	int front = 0;
	int back = index + 1;

	int STDOUT_FILENOx = dup(STDOUT_FILENO);
	int STDIN_FILENOx = dup(STDIN_FILENO);

	int fds[2];
	pipe(fds);
	dup2(STDOUT_FILENO, fds[0]);

	pid = fork();

	if (pid == 0){
		//printf("child1 running.\n");
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		input[index] = 0;
		//printf("Child1 about to exit.\n");
		execvp(input[front], input);
	}else{
		pid2 = fork();
		if (pid == 0){
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			input = &input[back];
			//printf("Child2 about to exit.\n");
			execvp(input[0], input);
		}else{
			wait(&pid2);
		}
	}
	wait(&pid);

	dup2(STDOUT_FILENOx, STDOUT_FILENO);
  	dup2(STDIN_FILENOx, STDIN_FILENO);
  	close(STDOUT_FILENOx);
  	close(STDIN_FILENOx);


	//printf("Both exited.");
	printf("I think the pipe worked, but I have no idea where the ouput of the 2nd command went...\n");
	printf("The structure of the commented-out pipe function underneath this one seems sound, but calling dup2() gives me a seg fault.\n");
	return;
}

/*
void piper(char ** input){
	printf("Piping... \n");
	int index = find(input, "|");
	int front = 0;
	int back = index + 1;

	printf("\n");
	int STDOUTx = dup(STDOUT_FILENO);
	int STDINx = dup(STDIN_FILENO);

	int fds[2] = {0};
	int outcome = pipe(fds);
	//printf("%d\n", outcome);
	//dup2(STDOUT_FILENO, fds[0]);

	//printf("child1 running.\n");
	printf("fine\n");
	dup2(fds[1], STDOUT_FILENO);
	printf("fine\n");
	close(fds[1]);
	input[index] = 0;
	//printf("Child1 about to exit.\n");
	execute(input[front]);

	dup2(STDOUTx, STDOUT_FILENO);

	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	input = &input[back];
	//printf("Child2 about to exit.\n");
	execute(input[0]);

  	dup2(STDINx, STDIN_FILENO);
  	close(STDOUTx);
  	close(STDINx);


	//printf("Both exited.");
	printf("I think the pipe worked, but I have no idea where the ouput of the 2nd command went...\n");
	return;
}
*/

/*======== int find() ==========
Inputs: char ** input
		char * test
Returns: int

char ** input is target array of pointers.
char * test is character that is looked for.
Returns location of test in input.
If not found, returns -1.
====================*/
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

/*======== void execute() ==========
Inputs: char ** input
Returns: void

Takes parsed command from ' ' delimiter parser.
Checks for exit commands, change of directory, redirection, or pipe.
Calls appropriate function or executes command itself if no special requirement is needed.
====================*/
void execute(char ** input){//executes program
	printf("Executing...\n\n");

	if(! strcmp(input[0], "exit")){//implementation of exit
		exit(0);
	}
	if(find(input, "|") != -1){
		piper(input);
	}else{
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
}

/*======== void printInput() ==========
Inputs: char ** input
Returns: void

Accepts array of pointers.
Prints the array of pointers in a nicely formatted way.
====================*/
void printInput(char ** input){//prints parsed command
	int x = 0;
	while(input[x]){
		printf("Input[%d] = %s\n", x, input[x]);
		x++;
	}
	return;
}

/*======== int countArgs() ==========
Inputs: char ** input
Returns: int

Counts number of arguments in array of pointers.
Returns that number.
====================*/
int countArgs(char ** input){
	int x = 0;
	while(input[x]){
		x++;
	}
	return x - 1;
}
