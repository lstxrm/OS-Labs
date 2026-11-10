
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2];
    int fd2[2];

    int status;
    char byte;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    int id = fork();

    if (id < 0) {
        perror("fork");
        exit(1);
    }

    if (id == 0) {
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], &byte, sizeof(byte));
        printf("%d: received ping\n", getpid());

        byte = 'c';
        write(fd2[1], &byte, sizeof(byte));

        close(fd1[0]);
        close(fd2[1]);
    }
    else {
        close(fd1[0]);
        close(fd2[1]);

        byte = 'p';
        write(fd1[1], &byte, sizeof(byte));

        read(fd2[0], &byte, sizeof(byte));
        printf("%d: received pong\n", getpid());

        close(fd1[1]);
        close(fd2[0]);

        wait(&status);
    }

    return 0;
}