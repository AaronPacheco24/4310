#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int fd;
    char ch;
    char readingbuffer[100];
    char writingbuffer[100];
    char userchoice;    
    int i=0;
    char kernout;
    char z;
    fd = open("/dev/test_module", O_RDWR);
    if (fd == -1)
    {
        printf("\nERR: Could not open file! Abort!\n");
        return 1;
    }
    printf("Welcome to Rock Paper Scissors. You will choose, and so will the 
kernel.\n");
    while (1){
        printf("\nMake your Selection\n");
        scanf(" %[^\n]",writingbuffer);
        write(fd,writingbuffer,sizeof(writingbuffer));
        read(fd,readingbuffer,sizeof(readingbuffer));
        switch (writingbuffer[0])
        {
        case 'r':
        case 'R':
            if (readingbuffer[0] == 'R') printf("Kernel Selected R ->DRAW\n");
            if (readingbuffer[0]== 'P') printf("Kernel Selected P -> LOSS\n");
            if (readingbuffer[0]== 'S') printf("Kernel Selected S -> WIN \n");
            break;
        case 'p':
        case 'P':
            if (readingbuffer[0] == 'R') printf("Kernel Selected R ->WIN\n");
            if (readingbuffer[0]== 'P') printf("Kernel Selected P -> DRAW\n");
            if (readingbuffer[0]== 'S') printf("Kernel Selected S -> LOSS \n");
            break;
        case 's':
        case 'S':
            if (readingbuffer[0]== 'R') printf("Kernel Selected R ->LOSS\n");
            if (readingbuffer[0]== 'P') printf("Kernel Selected P -> WIN\n");
            if (readingbuffer[0]== 'S') printf("Kernel Selected S -> DRAW \n");
            break;
        
        default:
            printf("ERR READING VALUE");
            return 1;
            break;
        }
    }
      close(fd);
    return 0;
}
