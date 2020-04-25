#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc < 2){
		printf("No Input");
		return 0;
	}
	pid_t pid;
	int status;
	pid = fork();
    if (pid == -1){
		printf("Can't create a process");
		exit(EXIT_FAILURE);
    }
	if(pid == 0){
		char *envr[] = { NULL };
		char *new[argc-1];
		for(int i = 0; i < argc-1; i++){
			new[i] = argv[i+1];
		}
		new[argc-1] = NULL;
		execve(argv[1], new, envr);
		exit(EXIT_SUCCESS);
	}else{
		fprintf(stderr, "%s: $$ = %d\n", argv[1], pid);
		waitpid(pid, &status, WUNTRACED);
		fprintf(stderr, "%s: $? = %d\n", argv[1], status);
	}
	return 0;
}
