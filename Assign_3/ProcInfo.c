// Ayush Jain - 2017UCP1168
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char *args[4];
    if(argc == 1){
        args[0] = strdup("./machineInfo");
        args[1] = NULL;
        execvp(args[0],args);
    }else if(argc == 3){
        args[0] = strdup("./systemInfo");
        args[1] = strdup(argv[1]);
        args[2] = strdup(argv[2]);
        args[3] = NULL;
        execvp(args[0],args);
    }else{
	args[0] = strdup("./ProcessInfo");
	args[1] = strdup(argv[1]);
	args[2] = NULL;
	execvp(args[0],args);
    }

    return 0;
}
