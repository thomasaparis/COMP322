#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

static int flag = 0;

struct Philosopher{
    int seats;
    int pos;
    int cycle;
    sem_t* chopstick[2];
    sem_t* returnVal;
    char buffer1[32];
    char buffer2[32];   
}phil;

void eat(){
    printf("Philosopher %d is eating.\n", phil.pos);
    usleep(rand() % 9999999);
}

void think(){
    printf("Philosopher %d is thinking\n", phil.pos);
    usleep(rand() % 9999999);
}

void handleSig(int sig){
    signal(SIGTERM, handleSig);
    if (sig == SIGTERM){
        sem_close(phil.chopstick[0]);
        sem_close(phil.chopstick[1]);
        sem_unlink(phil.buffer1);
        sem_unlink(phil.buffer2);
        flag = 1;
        }
    fprintf(stderr, "Philosopher [%d] completed %d cycles\n", phil.pos, phil.cycle);
}

int main(int argc, char **argv){ 
    if(argc != 3){
        printf("Arguments required: 2, Arguments provided:%d \n", argc);
        exit(EXIT_FAILURE);
    }
    phil.seats = atoi(argv[1]);
    phil.pos = atoi(argv[2]);
    phil.cycle = 0;
    if(phil.pos > phil.seats){
        fprintf(stderr, "Seats are not avaliable for philosopher: %d \n", phil.pos);
        return 0;
    }
    char chopst_name1[32];
    char chopst_name2[32];
    sprintf(chopst_name1, "%d", phil.pos);
    sprintf(chopst_name2, "%d", (phil.pos+1) % phil.seats);
    phil.buffer1[0] = '/';  
    strcat(phil.buffer1, chopst_name1);
    phil.buffer2[0] = '/';  
    strcat(phil.buffer2, chopst_name2); 
	phil.returnVal = sem_open(phil.buffer1, O_CREAT, 0666, 1);
    if(phil.returnVal == SEM_FAILED)
        perror("Can't create semaphore 0");
    phil.chopstick[0] = phil.returnVal;
    phil.returnVal = sem_open(phil.buffer2, O_CREAT, 0666, 1);
    if(phil.returnVal == SEM_FAILED)
        perror("Can't create semaphore 1");
    phil.chopstick[1] = phil.returnVal;
    if(signal(SIGTERM, handleSig) == SIG_ERR )
        fprintf(stderr, "Can't handle signal");
    int semVal0, semVal1;
    do{
        sem_getvalue(phil.chopstick[0], &semVal0);
        sem_getvalue(phil.chopstick[1], &semVal1);
        if(semVal0 != 0 || semVal1 != 0){
            sem_wait(phil.chopstick[0]);
            sem_wait(phil.chopstick[1]);
            eat(phil.pos);
            sem_post(phil.chopstick[0]);
            sem_post(phil.chopstick[1]);
            think(phil.pos);
            phil.cycle = phil.cycle + 1;
        }
    }while (flag == 0);
}
