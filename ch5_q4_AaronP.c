//Question 4: Write a program that calls fork() and then calls some form of
//exec() to run the program /bin/ls. See if you can try all of the
//variants of exec(), including (on Linux) execl(), execle(),
//execlp(), execv(), execvp(), and execvpe(). Why do
//you think there are so many variants of the same basic call?
//Group C--CAB12
//Aaron Pacheco
//Huan SHeng Chen
//Eric Tran
//What are the arguments for the execute variant that we used.
//Who is executing line 27?
//What can you say about the id subprocess?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int id_subprocess = fork();

    switch(id_subprocess)
    {
        case -1:
            printf("failed process, no child created\n\n")''
            exit(1);
            break;
        case 0:
            printf("print from child process\n\n");
            execvp("ls", argv);
            break;
        default:
            printf("print from parent process\n\n");
    }


    // if(id_subprocess == 0){ //line exe by both
    //     printf("print from child process\n\n");
    // }
    // if(id_subprocess > 0){ //line exe by both
    //     printf("print from parent process\n\n");
    // }

    // printf("print from both process\n\n"); //exe by both

    return 0;
}