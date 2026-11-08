#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(){
    int fd = open("output.txt", O_RDONLY | O_CREAT);
    close(fd);
    exit(0);
}