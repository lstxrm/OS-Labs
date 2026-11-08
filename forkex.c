#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int pid, status;

    pid = fork();
    if(pid == 0){
        char *argv[] = {"echo", "hello", "this", "is", "ECHO", 0};
        execvp("echo", argv);
        printf("exec failed\n");
        exit(1);
    }
    else{
        printf("PARENT waiting\n");
        wait(&status);
        printf("the child exited with status %d\n", status);
    }
    exit(0);
}