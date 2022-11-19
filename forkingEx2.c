
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
