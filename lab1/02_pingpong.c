#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p2c[2];
    int c2p[2];

    int status;
    char byte;

    if(pipe(p2c) == -1 || pipe(c2p) == -1){
        perror("Error occcured in constructing the pipe\n");
        return 1;
    }

    int id = fork();
    if(id == -1){
        printf("Error occured due to fork\n");
        return 2;
    }

    if(id == 0){
        close(p2c[1]);
        close(c2p[0]);
        int n = read(p2c[0], &byte, sizeof(char));
        if(n == -1){
            printf("Error occured on child read\n");
            return 3;
        }
        printf("%d: received ping\n", getpid());
        fflush(stdout);
        close(p2c[0]);
        byte = 'c';
        int we = write(c2p[1], &byte, sizeof(char));
        if(we == -1){
            printf("Error occured during writing to the pipe\n");
            return 4;
        }
        
        close(c2p[1]);
    }
    else{
        close(p2c[0]);
        close(c2p[1]);
        byte = 'p';
        int m = write(p2c[1], &byte, sizeof(char));
        if(m == -1){
            printf("Error occured during writing the source\n");
            return 5;
        }
        close(p2c[1]);
        int p = read(c2p[0], &byte, sizeof(char));
        if(p == -1){
            printf("Error occured during reading in the parent\n");
            return 6;
        }
        printf("%d: received pong\n", getpid());
        wait(&status);
        
        close(c2p[0]);
    }

    return 0;
}