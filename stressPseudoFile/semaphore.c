#include "semaphore.h"
#include <stdlib.h>
#include <stdio.h>

static pthread_mutex_t* pseudoFileSemaphore;

#define E_ERR 0
#define E_OK  1

int32_t semaphore_createPseudoFileSemaphore(void)
{
	int32_t result = E_ERR;

    pseudoFileSemaphore = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));

    if (pseudoFileSemaphore != NULL)
    {
    	result = E_OK;
    }

	return result;
}

void semaphore_deletePseudoFileSemaphore(void)
{
	int32_t result = E_ERR;

	free(pseudoFileSemaphore);
}

int32_t semaphore_openPseudoFile(int* fileDescriptor,
		                         const char* processDescriptor,
					             int mode)
{
	int32_t result = E_ERR;

	result = semaphore_lockQnxSemaphore();

	if (result)
	{
		*fileDescriptor = open(processDescriptor, mode);
		if (*fileDescriptor == -1)
		{
			result = E_ERR;
		}
	}

	return result;
}

int32_t semaphore_closePseudoFile(int fileDescriptor)
{
	int32_t result;

	result = (close(fileDescriptor) == E_ERR);

	semaphore_unlockQnxSemaphore();

	return result;
}

int32_t semaphore_lockQnxSemaphore(void)
{
	int32_t result = E_ERR;

    result = ((pthread_mutex_lock(pseudoFileSemaphore) == E_ERR));

    return (result == E_OK);
}

void semaphore_unlockQnxSemaphore(void)
{
	pthread_mutex_unlock(pseudoFileSemaphore);
}
