// Ayush Jain - 2017UCP1168 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int read_rate,out_rate,time;
    read_rate = atoi(argv[1]);
    out_rate = atoi(argv[2]);
    int no_of_samples = out_rate/read_rate;
    time = 0;

    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    char tmp1[50],tmp2[50],tmp3[50],tmp4[50];

    int free_mem = 0;
    int user_time = 0,kernel_time = 0, idle_time = 0;
    int tmp,var1,var2,var3,var4,var5;
    int context_switch,interrupts;

    while (1) {
        //Remember to close the file descriptors
        fp1 = fopen("/proc/meminfo","r");
        fscanf(fp1,"%s %s %s %s",tmp1,tmp2,tmp3,tmp4);
        fscanf(fp1,"%d",&tmp);
        free_mem = free_mem + tmp;

        fp2 = fopen("/proc/stat","r");
        fscanf(fp2,"%s %d %d %d %d",tmp1,&var1,&var2,&var3,&var4);
        user_time = user_time + var1;
        kernel_time = kernel_time + var3;
        idle_time = idle_time + var4;

        while(strcmp(tmp1,"intr") != 0){
            fscanf(fp2,"%s",tmp1);
        }
        fscanf(fp2,"%d",&interrupts);

        while(strcmp(tmp1,"ctxt") != 0){
            fscanf(fp2,"%s",tmp1);
        }
        fscanf(fp2,"%d",&context_switch);

        time = time + read_rate;
        fclose(fp1); fclose(fp2);
        sleep(read_rate);

        if(time == out_rate){
            printf("Average available memory : %d\n",free_mem/no_of_samples);
            printf("Average CPU User Time : %d\n",user_time/no_of_samples);
            printf("Average CPU Kernel Time : %d\n",kernel_time/no_of_samples);
            printf("Average CPU idle time : %d\n",idle_time/no_of_samples);
            printf("Context Switches so far : %d\n",context_switch);
            printf("Interrupts Serviced so far : %d\n",interrupts);
            printf("\n");
            free_mem = user_time = kernel_time = idle_time = 0;
            time = 0;
        }
    }

    return 0;
}
