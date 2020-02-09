//Demonstrating Zombie Processes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    }else if (pid == 0) {
        printf("In child process(pid = %d)\n",(int)getpid());
        exit(0);
    } else {
        char *args[3];
        args[0] = strdup("ps");
        args[1] = NULL ; args[2] = NULL;
        sleep(3);
        execvp(args[0],args);
    }
    return 0;
}
/*
//Demonstrating Orphan Processes
int main(int argc, char* argv[]){
    int pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    }else if (pid == 0) {
        printf("In child process(pid = %d)\n",(int)getpid());
        char *args[3];
        args[0] = strdup("ps");
        args[1] = NULL ; args[2] = NULL;
        sleep(3);
        execvp(args[0],args);
    } else {
        exit(0);
    }
    return 0;
}
*/
