
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void do_work(char*);
int main(int argc, char *argv[])
{
    printf("\nI am : %d \n", (int)getpid());
    pid_t pid = fork();
    srand((int)pid);
    if (pid<0){
        perror("Fork failed \n");
    }
    if ( pid ==0)
    {
        printf("I am the child process. I have PID %d \n", (int)getpid());
        do_work("Child");
        printf("Child exiting..\n");
        exit(42);
    }
    printf("Parent... Waiting for child to finish:\n");
    do_work("Parent");
    int status = 0;
    pid_t childpid = wait(&status);
    int childRet = WEXITSTATUS(status);
    printf("Parent knows child has status %d \n", childRet);
    printf("Parent ending\n");
    
}
void do_work(char *name){
    const int NUM_TIMES =5;
    for (int i =0;i<NUM_TIMES;i++){
        sleep(rand()%4);
        printf("%d iteration of work done complete\n",i); 
    }
    
}
