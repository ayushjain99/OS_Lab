// Implementation of McGuires solution for N-process
// critical section
// 2017UCP1168
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE 1
#define PERMS 0666 // For R/W permissions

const int N = 6;
const int loopMax = 200;
enum Status {IDLE, WANT_IN, IN_CS};

double elapsed;
int x = 2;
int *flag;
int *turn = 0;
int *counter = 0;
clock_t start, stop;

void Process(int i) {
	int j, index = 0;
	printf("Child: %d began running!\n", i);
	sleep(3);
	while(index < loopMax) {
		while (1) {
			*(flag+i) = WANT_IN;
			j = *turn;
			while (j != i) {
				if (*(flag+j) != IDLE)
					j = *turn;
				else
					j = (j + 1) % N;
			}

			*(flag+i) = IN_CS;
			j = 0;

			while ((j < N) && ((j == i) || (*(flag+j) != IN_CS))) {
				j = j + 1;
			}

			if((j >= N) && (*turn == i || (*(flag+*turn) == IDLE)))
				break;
		}
		*turn = i;

		/* CRITICAL SECTION */
		stop = clock();
		elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
		printf("Process %d took %f milliseconds to enter the CS!\n", i, elapsed);
		printf("Process %d with index %d\n", i, index+1);
		printf("Process %d ", i);
		printf(" has entered the critical section and went to sleep!\n");
		sleep(1);
		printf("Process %d ", i);
		*counter = *counter + i;
		printf(" has woke up and updated the counter to %d \n", *counter);

		/* END OF CRITICAL SECTION */
		start = clock();

		j = (*turn + 1) % N;
		while (*(flag+j) == IDLE) {
			j = (j + 1) % N;
		}
			*turn = j;
			*(flag+i) = IDLE;
		index++;
	}
}

int main(void) {
	int i, pid, shmid;

	/* Initialize Shared Memory */
	counter = mmap(NULL, sizeof *counter, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANON, -1, 0);
	*counter = 0;
	turn = mmap(NULL, sizeof *turn, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANON, -1, 0);
	*turn = 0;

	if((shmid = shmget(1000, BUFSIZE, IPC_CREAT | PERMS)) < 0) {
		printf("\n unable to create shared memory");
 		return 0;
	}

	/* Initialize Shared Array */
	if((flag=(int*)shmat(shmid,(char*)0,0)) == (int*)-1) {
  		printf("\n Shared memory allocation error\n");
  		exit(1);
	}

	int loopIndex;
	for(loopIndex = 0; loopIndex < N; loopIndex++)
		*(flag+loopIndex) = IDLE;

	int child;
	for (child = 0; child < N; child++) {
    	pid = fork();
    	if (pid)
        	continue;
    	else if (pid == 0) {
    		Process(child);
        	break;
    	} else {
        	printf("Fork error!\n");
        	exit(1);
    	}
	}

	return 0;
}
