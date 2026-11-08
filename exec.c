#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
    char *argv[] = {"echo", "hello", "world", 0};
    execvp("echo", argv);
    printf("Error occured");
    exit(0);
}