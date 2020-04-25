#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

static const char* signals[27] = {  "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE","USR1", 
                                    "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", 
                                    "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};

void handle_reg(int mysig) {
    signal(mysig, handle_reg);
    static int ctTERMs, totalSIGNALs = 0;
    time_t startTime;
    time(&startTime);
    printf(stderr,"SIG%s caught at %\n", signals[mysig-1], (int)startTime);
    totalSIGNALs++;
    if(mysig == SIGTERM){
        ctTERMs++;
    }else{
        ctTERMs = 0;
    }
    if(ctTERMs == 3){
        fprintf(stderr, "catcher: Total signals count = %d\n" , totalSIGNALs);
        exit(EXIT_SUCCESS);
    }
}

int sigNum(char*sig){
    int retSignal = -1;
    for(unsigned int i = 0; i < 27; i++){
        if(strcmp(sig, signals[i]) == 0){
            retSignal = i;
        }
    }
    return ++retSignal;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("No Input");
        return 0;
    }
    fprintf(stderr, "%s: $$ = %d\n", argv[0], getpid());
    for(int i = 1; i < argc; i++){
        if(signal(sigNum(argv[i]), handle_reg) == SIG_ERR )
            fprintf(stderr, "Signal ERROR");
    }
    while(1){
        pause();
    }
    return 0;
}
