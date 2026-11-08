#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    int x = fork();
    if(x>0){
        printf("I am the parent with pid %d returning %d\n", getpid(), x);
    }
    else if(x==0){
        printf("I am the child with pid %d with parent pid %d returning %d\n", getpid(), getppid(), x);
    }
    else{
        printf("Error occured");
    }
}