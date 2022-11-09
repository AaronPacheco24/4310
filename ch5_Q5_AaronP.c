//Seminar1 Question 5:  Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if
//you use wait() in the child
//Group C--CAB12
//Aaron Pacheco
//Huan Sheng Chen
//Eric Tran
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    int subproc_ID = fork();//create the fork
    if ( subproc_ID == 0)
    {
        printf("\nThis is child process\n"); //print that we are proceeding in child subprocess
        int wait_return = wait(NULL); // Get the return value for the wait
        printf("\n The wait() in the child returned: %d\n", wait_return); //The value is -1. man wait states this is to be expected due to it waiting for a child
    }//however it is negative one because it is waiting for the child of the child. Which has not been created. 
    else if ( subproc_ID <0 )
    {
        printf("\nfork failed\n");
    }
    else
    {
        printf("\n this is parent process\n");
        int wait_returnp = wait(NULL); // Returns The ID of the child
        printf("\nThe wait() in the parent returned %d\n", wait_returnp); // output the result from waiting for the child to finish.
    }

    return 0;
}