#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char * getInput(){//Obtains user input
	char * cmd = (char *) malloc(1000);
	printf("----------------Enter a command: ");
	fgets(cmd, 1000, stdin); //sizeof does not work
	char * r = strchr(cmd, '\n');//strchr returns pointer, set to zero to remove /n
	*r = 0;
	//printf("%s\n", cmd);
	return cmd;
}

char ** parse(char * cmd){//Parses and prepares user input
	printf("Full Input: %s\n", cmd);
	char ** input = (char **) malloc(1000);
	char * s = cmd;
	char * p = cmd;
	int x = 0;
	while (s){
		input[x] = strsep(&s, " "); //parsing / separating command
		//printf("input[%d]: %s\n", x, input[x]);
		x++;
	}
	input[x] = 0; //adding terminiating NULL to array
	return input;
}

int execute(char ** input){//executes program
	printf("Executing...\n\n");

	if(! strcmp(input[0], "exit")){//implementation of exit
		exit(0);
	}

	int pid = fork();
	if (pid == 0){
		execvp(input[0], input);
	}else{
		wait(&pid);
	}

	return 0;
}

void printInput(char ** input){//prints parsed command
	int x = 0;
	while(input[x]){
		printf("Input[%d] = %s\n", x, input[x]);
		x++;
	}
	return;
}
