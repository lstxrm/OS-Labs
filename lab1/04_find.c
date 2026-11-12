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
    if(fd < 0) return;
    if(fstat(fd, &st) < 0){
        close(fd);
        return;
    }
    switch(st.type){
    case T_FILE: {
        char* name = path;
        for(char* p = path; *p; p++){
            if(*p == '/') name = p+1;
        }
        if(strcmp(name, target) == 0){
            printf("%s\n", path);
        }

        break;
    }
    case T_DIR:{
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0) continue;
            if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
            char buf[512];
            strcpy(buf, path);
            strcat(buf, "/");
            strcat(buf, de.name);
            
            find(buf, target);
            break;
        }
    }
    }
    close(fd);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: find <path> <filename>\n");
        exit(1);
    }
    find(argv[1], argv[2]);

    exit(0);
}