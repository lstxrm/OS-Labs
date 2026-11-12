#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<stdbool.h>

int main(){
    int p[2];

    if(pipe(p) == -1){
        perror("pipe");
        return 1;
    }
    int id = fork();
    if(id == 0){
        close(p[1]);
        int input = p[0];

        while(1){
            int prime;
            ssize_t n = read(input, &prime, sizeof(int));

            if(n == 0) break;
            if(n != sizeof(int)){
                perror("read");
                exit(1);
            }
            printf("prime %d\n", prime);
            fflush(stdout);

            int next[2];

            if(pipe(next) == -1) {
                perror("pipe");
                exit(1);
            }
            int pid = fork();

            if(pid == -1){
                perror("fork");
                exit(1);
            }
            if(pid == 0){
                close(next[1]);
                close(input);
                input = next[0];
                continue;
            }
            close(next[0]);

            int num;
            while((n = read(input, &num, sizeof(int))) == sizeof(int)){
                if(num % prime != 0){
                    if(write(next[1], &num, sizeof(int)) != sizeof(int)){
                        perror("write");
                        exit(1);
                    }
                }
            }
            close(input);
            close(next[1]);
            wait(NULL);
            return 0;
        }
        close(input);
        return 0;
    }

    else{
        close(p[0]);
        for(int i = 2; i <= 35; i++){
            if(write(p[1], &i, sizeof(int)) != sizeof(int)){
                perror("write");
                break;
            }
        }

        close(p[1]);
        wait(NULL);

        return 0;
    }
}