#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "ERROR: input required");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}