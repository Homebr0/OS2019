#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int SharedVariable = 0; //will be keeping track of the processes done by threads
void SimpleThread(int which)
{
	int num, val;
	for(num = 0; num < 20; num++)
	{
		if(rand() > RAND_MAX/2)
		{
			usleep(10);
		}
		val = SharedVariable;
		printf("***Thread %d sees value %d\n", which + 1, val);
		SharedVariable = val + 1;
	}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", which + 1, val);
}



int main(int argc, char *argv[])
{
	
		
	int i, k;
	
	//validates input is an integer
	for (k = 0; argv[1][k] != 0; k++)
	{
		
		if (!isdigit(argv[1][k]))
		{
			printf("Please enter an integer\n");
			exit(0);
		}
	}
	
	int numThread = atoi(argv[1]);
	
	//validates for only one argument
	if (argc != 2)
	{
		printf("Invalid number of arguments!\n");
		exit(0);
	}

	//validates that the user input a valid amount of threads
	for (k = 0; k < numThread; k++)
	{
		if (numThread < 1 || numThread > 200)
		{
			printf("Please enter a number 0 - 200!\n");
			exit(0);
		}
	}

	
	pthread_t myThread[numThread];
	int tid[numThread];
	
	//The threads are created
	for(i = 0; i < numThread; i++)
	{
		tid[i] = i;
		pthread_create(&myThread[i], NULL, SimpleThread, (void *) tid[i]);
	}

	//The threads are joined	
	for (i = 0; i < numThread; i++)
	{
		pthread_join(myThread[i], NULL);
	}

	return 0;

}


	
