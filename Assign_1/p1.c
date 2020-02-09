#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("hello world (pid:%d)\n", (int) getpid());
    int var = 5;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        var = 10;
        printf("hello, I am child (pid:%d), var = %d\n",(int)getpid(),var);
    } else {
        // parent goes down this path (original process)
        sleep(3);
        printf("hello, I am parent of %d (pid:%d), var = %d\n",rc,(int)getpid(),var);
    }
    return 0;
}
