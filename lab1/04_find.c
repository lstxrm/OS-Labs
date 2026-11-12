#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include "kernel/stat.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


void find(char* path, char* target){
    int fd;
    struct stat st;
    struct dirent de;
    fd = open(path, 0);
    fstat(fd, &st);
    switch(st.type){
    case T_FILE:
        if(de.name == target)



    case T_DIR:
        while(read(fd, &de, sizeof(de)) == sizeof(de)){

        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: find <path> <filename>\n");
        exit(1);
    }
    find(argv[1], argv[2]);

    exit(0);
}