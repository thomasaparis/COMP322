#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1

int commaPos(char **argv, int argc){
	int index = -1;
	for(int i = 0; i < argc; i++){
		if(argv[i][0] == ','){
			index = i;
        }
	}
	return index;
}

void createNewArgv(char **argv, char **newArgv, int startAt, int size){
    int j = 0;
    for(int i = startAt; i < size; i++){
        newArgv[j] = argv[i];
        j++;
    }
    newArgv[j] = NULL;
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("No Input");
        return 0;
    }
    int pipeFD[2];
    pid_t child1;
    int status1, status2;
    int commaIndex = 0;
    char *envr[] = {NULL};
    if (pipe(pipeFD) == -1){
        printf("Can't allocate a pipe");
        exit(EXIT_FAILURE); 
    }
    commaIndex = commaPos(argv, argc);
    child1 = fork();
    if (child1 == -1){ 
        printf("Can't create a process 1");
        exit(EXIT_FAILURE);
    }else if(child1 == 0){
        dup2(pipeFD[WRITE_END], 1);
        char *newArgv[argc - commaIndex + 1];
        createNewArgv(argv, newArgv, 1, commaIndex);
        execve(newArgv[0], newArgv, envr);
        exit(EXIT_SUCCESS);
    }else{
        pid_t child2 = fork();
        if (child1 == -1){
            printf("Can't create a process 2");
            exit(EXIT_FAILURE);
        }else if(child2 == 0){
            dup2(pipeFD[READ_END], 0);
            char *newArgv[commaIndex];
            createNewArgv(argv, newArgv, commaIndex + 1, argc);
            execve(newArgv[0], newArgv, envr);
            exit(EXIT_SUCCESS);
        }else{
            fprintf(stderr, "%s: $$ = %d\n", argv[1], child1);
            fprintf(stderr, "%s: $$ = %d\n", argv[commaIndex+1], child2);
            close(pipeFD[0]);
            close(pipeFD[1]);
            waitpid(child2, &status2, WUNTRACED);
            waitpid(child1, &status1, WUNTRACED);
            fprintf(stderr, "%s: $? = %d\n", argv[1], status1);
			fprintf(stderr, "%s: $? = %d\n", argv[commaIndex+1], status2);
        }
    }
    return 0;
}
