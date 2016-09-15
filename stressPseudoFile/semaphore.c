#include "semaphore.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static pthread_mutex_t pseudoFileSemaphore = PTHREAD_MUTEX_INITIALIZER;

#define E_ERR 0
#define E_OK  1

int32_t semaphore_createPseudoFileSemaphore(void)
{
	int32_t result = E_ERR;

   // pseudoFileSemaphore = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));

    if (&pseudoFileSemaphore != NULL)
    {
    	result = E_OK;
    }

	return result;
}

void semaphore_deletePseudoFileSemaphore(void)
{
	int32_t result = E_ERR;

	//free(pseudoFileSemaphore);
}

int32_t semaphore_openPseudoFile(int* fileDescriptor,
		                         const char* processDescriptor,
					             int mode,
								 char* function)
{
	int32_t result = E_ERR;
    printf("[%s] semaphore_openPseudoFile\n", function);
	result = semaphore_lockQnxSemaphore(function);

	if (result == 1)
	{
		printf("[%s] inside open\n", function);
		(*fileDescriptor) = open(processDescriptor, mode);
		printf("[%s]inside open, I have the lock and fd is: %d\n", function, *fileDescriptor);
		printf("[%s]inside open fd: %d.\n", function, *fileDescriptor);
		if ((*fileDescriptor) == -1)
		{
			result = E_ERR;
		}
	}
	else {printf("[%s] ** semaphore problem\n", function);}

	return result;
}

int32_t semaphore_closePseudoFile(int fileDescriptor, char* function)
{
	int32_t result;

	//Close: 0 on success
	result = (close(fileDescriptor) == E_ERR);

	if (result == 0)
		printf("[%s] !!! error closing the fd\n", function);
	semaphore_unlockQnxSemaphore(function);

	return result;
}

int32_t semaphore_lockQnxSemaphore(char* function)
{
	int32_t result = E_ERR;

    result = ((pthread_mutex_lock(&pseudoFileSemaphore) == E_ERR));

    if (result == E_OK)
    {
    	printf ("[%s]+++++++++++++++++++++++++++++++++++++++++++++++++++ locked\n", function);
    }
    else
    {
    	printf("!!!!ERROR!!!!!!\n");
    }
    return result;
}

void semaphore_unlockQnxSemaphore(char* function)
{
	printf ("[%s]------------------------------------------------------- unlocked\n", function);
	pthread_mutex_unlock(&pseudoFileSemaphore);
}
