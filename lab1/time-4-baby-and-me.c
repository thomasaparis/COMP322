#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>

int report(){
    int status;
    pid_t pid = fork();
    if(pid<0){
        perror("forking failed");
    }else if(pid==0){
        printf("PPID: %d, ",(int)getppid());
        printf("PID: %d\n",(int)getpid());
        sleep(2);
        exit(EXIT_SUCCESS);
    }else{
        printf("PPID: %d, ", (int)getppid());
        printf("PID: %d, ",(int)getpid());
        printf("CPID: %d, ",pid);
        waitpid(pid,&status,0);
        if(WIFEXITED(status)){
            int returned = WEXITSTATUS(status);
            printf("RETVAL %d\n",returned);
        }
        sleep(1);
    }
    return (0);
}

int timer(int val){
    time_t seconds; 
    seconds = time(NULL); 
    if(val==0){
        printf("\nSTART: %ld\n", seconds);
    }else{
        printf("STOP: %ld  \n", seconds);
    }
    return (0);
}

int main(void){
    struct tms end_tms;
    timer(0);
    report();
    times(&end_tms);
    clock_t cpu_time = end_tms.tms_cutime;
    clock_t utime = end_tms.tms_utime;
    clock_t stime = end_tms.tms_stime;
    clock_t cstime = end_tms.tms_cstime;

    printf("USER: %ld, ", cpu_time);
    printf("SYS: %ld \n", utime);
    printf("CUSER: %ld , ", stime);
    printf("CSYS: %ld, \n", cstime);
  
    timer(1);
    return(0); 
}
