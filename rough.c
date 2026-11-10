#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){
    int pid, status;
    pid = fork();
    if(pid == 0){
        char* argv[] = {"echo", "hello", "this", "is", "ECHO", 0};
        execvp("echo", argv);
        printf("exec failed\n");
        exit(1);
    }
    else{
        printf("Parent waiting\n");
        wait(&status);
        printf("The child exited with status %d\n", status);
    }
    exit(0);
}