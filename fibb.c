#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>


int SharedVariable = 0;
pthread_mutex_t lock;
pthread_barrier_t barr;
int sequence[48];
int counter = 2;


void SimpleThread(int arg)
{

	int threadId = arg;
	int i;

	for (i = 0; i < 20; i++)
	{
#ifdef PTHREAD_SYNC
	pthread_mutex_lock(&lock);
#endif
    if(counter > 1)
    {
        sequence[counter] = (sequence[counter - 2] + sequence[counter - 1]);
        counter++;
    }


#ifdef PTHREAD_SYNC
	pthread_mutex_unlock (&lock);
#endif
	}

	pthread_barrier_wait (&barr);
	return NULL;

}

int main(int argc, char *argv[])
{
	int k, p;

	for (k = 0; argv[1][k] != 0; k++)
	{
		if (!isdigit(argv[1][k]))
		{
			printf("Please enter an integer 0 - 47!");
			exit(0);
		}
	}

	int numThread = atoi(argv[1]);

	int i, err;

	if (argc != 2)
	{
		printf("Invalid number of arguments!");
		exit(0);
	}

	for (k = 0; k < numThread; k++)
	{
		if (numThread < 0 || numThread > 47)
		{
			printf("Argument out of bounds! Please enter a number 0 - 47");
			exit(0);
		}
	}
	sequence[0] = 0;
    sequence[1] = 1;
	pthread_t threads[numThread];
	int threadIds[numThread];

	pthread_mutex_init (&lock, NULL);
	pthread_barrier_init (&barr, NULL, numThread);

	for (i = 0; i < numThread; i++)
	{
		threadIds[i] = i;

		err = pthread_create (&threads[i], NULL, SimpleThread, (void *) threadIds[i]);
		if (err)
		{
			printf("Error creating threads, return code %d\n", err);
			exit(-1);
		}
	}

	for (i = 0; i < numThread; i++)
	{
		pthread_join (threads[i], NULL);

		for(p = 0; p <= i; p++)
		{
		    printf("%d", sequence[p]);

		    if(p != i)
		    {
		       printf(", ");
		    }

		}
		printf("\n");
	}


	return 0;
}
