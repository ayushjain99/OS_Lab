// SHARING MEMORY BETWEEN PROCESSES
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	int shmid, status;
	int *a, *b;
	int i;

	shmid = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
    a = (int*) shmat(shmid,0,0);
    *a = 500; // Initialize balance to 500
    shmdt(a);

	if (fork() == 0) {
		// Child Process 1 -> withdraw 200
		// shmat() returns a char pointer which is typecasted to int pointer
		b = (int*) shmat(shmid,0,0);
        int tmp = *b;
        tmp = tmp - 200;
        sleep(1);
        // Context switch karvana padega, varna itne se stmts ek saath execute ho
        // he jaate hai
        *b = tmp;
		shmdt(b);
	} else {
        if (fork() == 0) {
            // Child Process 2 -> deposit 400
            a = (int*)shmat(shmid,0,0);
    		int tmp = *a;
            tmp = tmp + 400;
            *a = tmp;
            /* each process should "detach" itself from the
               shared memory after it is used */
    		shmdt(a);
        } else {
            while(wait(&status) > 0) ;
            a = (int*) shmat(shmid,0,0);
            printf("\nFinal value of balance = %d\n",*a);
            printf("Correct value should have been 700\n");
            printf("Hence race condition demonstrated\n\n");
            shmdt(a);
    		/* Now the main process should delete the cretaed shared memory */
            /* since both child have exited */
    		shmctl(shmid, IPC_RMID, 0);
        }
	}
}
