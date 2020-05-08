// February 24, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_ARGS 1024
#define MAX_HIST_SIZE 10000

char* getinput(FILE* fp, size_t size){
	char* str;
	int ch;
	size_t len = 0;

	str = realloc(NULL, sizeof(char)*size);

	if(!str)
		return str;

	ch = fgetc(fp);

	while(ch != EOF && ch != '\n'){
		str[len++] = ch;
		if(len == size){
			str = realloc(str, sizeof(char)*(size*=2));
			if(!str)
				return str;
		}
		ch = fgetc(fp);
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char)*len);
}

int main (void){

	int cmdtype, numcommands = 0, i = 0, j = 0, k = 0;
	int killpid;
	char* rawinput;
	char path[PATH_MAX];
	char* args; 
	char* argv[NUM_ARGS];
	char* nextarg;
	struct stat stats;
	char* history[MAX_HIST_SIZE];
	pid_t child;

	while(1){
		
		// print command prompt
		printf("\n# ");

		// Get raw input string
		rawinput = getinput(stdin, 256);
		if(rawinput == NULL)
			continue;
		
		history[k++] = realloc(rawinput, sizeof(rawinput));
		//strcpy(history[i], rawinput);
		// get base command
		char *args = strtok(rawinput, " ");

		if(args == NULL)
			continue;

		// initialize array
		for(i = 0; i < NUM_ARGS; i++)
			argv[i] = NULL;

		if (strcmp(args, "changedir") == 0)
			cmdtype = 1;
		else if (strcmp(args, "whereami") == 0)
			cmdtype = 2;
		else if (strcmp(args, "lastcommands") == 0)
			cmdtype = 3;
		else if (strcmp(args, "quit") == 0)
			cmdtype = 4;
		else if (strcmp(args, "run") == 0)
			cmdtype = 5;
		else if (strcmp(args, "background") == 0)
			cmdtype = 6;
		else if (strcmp(args, "exterminate") == 0)
			cmdtype = 7;
		else
			continue;

		switch (cmdtype){
			case 1: // changedir
				// get argument of new dir
				strcpy(path, strtok(NULL, " "));
				if(chdir(path) != 0)
					printf("Error: %s\n", strerror(errno));
				break;
			case 2:// whereami
				getcwd(path, sizeof(path));
				if(path != NULL)
					printf("%s\n", path);
				break;
			case 3: // lastcommands
				// get next arg if any
				args = strtok(NULL, " ");
				// clear history if -c is included
				if(args != NULL && strcmp("-c", args) == 0){
					for(i = 0; i < MAX_HIST_SIZE; i++)
						history[i] = NULL;
					k = 0;
					break;
				}
				// Print out each item in history
				for(i = 0; i < MAX_HIST_SIZE; i++){
					if(history[i] != NULL)
						printf("%s\n", history[i]);
					else
						break;
				}
				break;		
			case 4: // quit
				exit(0);
				break;
			case 5: // run
				// get path
				args = strtok(NULL, " ");

				// check if file exitsts
				if(stat(args, &stats) != 0 && args[0] != '/')
					;
				else if(stat(args, &stats) != 0)
					printf("Error: %s\n", strerror(errno));

				argv[j] = realloc(argv[j], sizeof(args));
				strcat(argv[j++], args);
				
				// add arguments to the command path
				nextarg = strtok(NULL, " ");
				while(nextarg != NULL){
					argv[j] = realloc(argv[j], sizeof(nextarg));
					strcat(argv[j], nextarg);
					nextarg = strtok(NULL, " ");
					j++;
				}
				
				// execute program with args
				child = fork();
				if(child == -1){
					// error
					perror("Unable to fork.");
					exit(1);

				}else if(child > 0){
					int status;
					// wait for new process to exit
					printf("PID: %d created.", child);
					waitpid(child, &status, 0);

				}else{
					if(args[0] == '/')
						execv(args, argv);
					else
						execvp(args, argv);
				}
				
				break;
			case 6: // background
				// get path
				args = strtok(NULL, " ");

				// check if file exitsts
				if(stat(args, &stats) != 0 && args[0] != '/')
					;
				else if(stat(args, &stats) != 0)
					printf("Error: %s\n", strerror(errno));

				argv[j] = realloc(argv[j], sizeof(args));
				strcat(argv[j++], args);
				
				// add arguments to the command path
				nextarg = strtok(NULL, " ");
				while(nextarg != NULL){
					argv[j] = realloc(argv[j], sizeof(nextarg));
					strcat(argv[j], nextarg);
					nextarg = strtok(NULL, " ");
					j++;
				}
				
				// execute program with args
				child = fork();
				if(child == -1){
					// error
					perror("Unable to fork.");
					exit(1);

				}else if(child > 0){
					
					// wait for new process to exit
					waitpid(child, NULL, WNOHANG);
					printf("PID: %d created.", child);
					break;

				}else{
					if(args[0] == '/')
						execv(args, argv);
					else
						execvp(args, argv);
				}
				break;
			case 7: // exterminate
				killpid = atoi(strtok(NULL, ""));
				if(kill(killpid, SIGKILL) != 0)
					printf("Unable to kill process %d.\n", killpid);
				else
					printf("Successfully killed process %d.\n", killpid);
				break;	
			default:
				break;


		}

	}

	// cleanup
	for(i = 0; i < NUM_ARGS; i++)
		free(argv[i]);
	free(argv);
	free(rawinput);
	free(args);
	free(nextarg);

	return 0;
}
