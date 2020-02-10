// Ayush Jain - 2017UCP1168
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE *fp = fopen("/proc/cpuinfo","r");
    char* line = NULL; size_t len;
    char search[100]; char* p;
    while(getline(&line,&len,fp) != -1){
        p = strstr(line,"processor");
        if(p != NULL)
            printf("\n%s",line);
        p = strstr(line,"model name");
        if(p != NULL)
            printf("%s",line);
        p = strstr(line,"cpu cores");
        if(p != NULL)
            printf("%s",line);

    }
    fclose(fp); fp = fopen("/proc/version","r");
    printf("\nVersion of Linux Kernel : ");
    while(getline(&line,&len,fp) != -1){
        printf("%s",line);
    }
    fclose(fp); fp = fopen("/proc/meminfo","r");
    printf("\nAmount of Memory Configured :\n");
    for (size_t i = 0; i < 3; i++) {
        getline(&line,&len,fp);
        printf("%s",line);
    }
    printf("\nAmount of time since the system was last booted : ");
    fclose(fp); fp = fopen("/proc/uptime","r");
    float uptime;
    fscanf(fp,"%f",&uptime);
    int days,hours,min,sec;
    days = (uptime/3600)/24;
    hours = (uptime/3600) -(days*24);
    min = (uptime/60) - (hours*60);
    sec = (uptime) - (min*60);
    printf("%d:%d:%d:%d\n\n",days,hours,min,sec);
    return 0;
}
