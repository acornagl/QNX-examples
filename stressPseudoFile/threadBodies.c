#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/procfs.h>
#include <sys/neutrino.h>
#include <sys/types.h>
#include <sys/syspage.h>
#include <errno.h>
#include <fcntl.h>

#include "threadBodies.h"

#define YES 1
#define NO  0

#define ERR 1
#define OK  0

#define KB (1024/sizeof(int32_t))
#define KB_TO_TRACE 1000
#define TRACED_ELEMENTS (KB_TO_TRACE * KB)
#define MAX_N_CPUS 4

static   int   pidToAccess   = -1;
static   int   tidToChange   = -1;
volatile int   infoAvailable = NO;
volatile int   terminate     = NO;
static   char* pseudoFile = "";
int32_t traceCpus[KB_TO_TRACE * KB] = {-1};

void* threadBodies_readBody(void* ptr)
{
	int32_t processID = getpid();
	int32_t thisId = pthread_self();
	int32_t fileOpenResult = ERR;
	int32_t pseudoFileDescriptor = -1;
	int32_t result = ERR;
	int32_t count = 0;

	pidToAccess = processID;
	tidToChange = thisId;

	semaphore_lockQnxSemaphore(__func__);
	{
		char* prefix = "/proc/";
		char* suffix = "/as";
		pseudoFile = (char*)malloc(1024);
		sprintf(pseudoFile, "%s%d%s", prefix, processID, suffix);
		infoAvailable = YES;
	}
	semaphore_unlockQnxSemaphore(__func__);

	// Thread main action
	while (!terminate)
	{
		double a = 15487651.2;
		int q = 1;
		for (; q < 10; q++)
		{
			a = (a+q)/a + 1;
		}
		printf("==read==\n");
		fileOpenResult = semaphore_openPseudoFile(&pseudoFileDescriptor,
				                                  pseudoFile, O_RDONLY, __func__);
		if (pseudoFileDescriptor != -1)
		{
			procfs_status status;
			status.tid = __tls()->__tid;
			result = _devctl(pseudoFileDescriptor, DCMD_PROC_TIDSTATUS, &status,
					         sizeof(status), 0);
			if (result == EOK)
			{
				traceCpus[count] = status.last_cpu;
			}
		}

		semaphore_closePseudoFile(pseudoFileDescriptor,__func__);

		count += 1;
		if (count == TRACED_ELEMENTS)
		{
			terminate = YES;
		}
	}
}

void* threadBodies_writeBody(void* ptr)
{
	int32_t fileOpenResult = ERR;
	int32_t pseudoFileDescriptor = -1;
	int32_t result = ERR;
	int32_t count = 0;
	char    cpusAffinity[MAX_N_CPUS] = {0x1, 0x2, 0x4, 0x8};


	while (!infoAvailable) {}

	// Thread main action
	while (!terminate)
	{
		double a = 15487651.2;
				int q = 1;
				for (; q < 1; q++)
				{
					a = (a+q)/a + 1;
				}
		printf("==write==\n");
		fileOpenResult = semaphore_openPseudoFile(&pseudoFileDescriptor,
				                                  pseudoFile, O_RDWR, __func__);

		if (pseudoFileDescriptor == -1)
		{
			printf(
			   "*** Error opening the pseudo-file.\n -- fd: %d\n -- name: %s -- Errno: %d, strerror(): %s\n",
			   pseudoFileDescriptor, pseudoFile, errno, strerror(errno));
			terminate = YES;
		}
		else
		{
			printf("affinity changed!\n");
			procfs_threadctl tctl;
			tctl.tid = tidToChange;// the read thread
			tctl.cmd = _NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT; // effective command
            // clean tctl.data
			int i = 0;

			for(; i < sizeof(tctl.data); i++)
			{
				tctl.data[i] = 0x0;
			}

			// set the affinity
			tctl.data[0] = 0x1; // mask of 1B
			tctl.data[1] = 0x0;
			tctl.data[2] = 0x0;
			tctl.data[3] = 0x0;
			tctl.data[4] = cpusAffinity[count % MAX_N_CPUS];
			tctl.data[5] = 0x0;
			tctl.data[6] = 0x0;
			tctl.data[7] = 0x0;
			tctl.data[8] = cpusAffinity[count % MAX_N_CPUS];

			// change the affinity;
			devctl(pseudoFileDescriptor, DCMD_PROC_THREADCTL, &tctl,
				   sizeof(tctl), NULL);
			count += 1;
		}
		semaphore_closePseudoFile(pseudoFileDescriptor,__func__);
	}
}

void threadBodies_freePseudoFile(void)
{
	free(pseudoFile);
}

void threadBodies_printVisitedCPUs(void)
{
	int32_t count = 0;

	for (; count < 50; count += 1)
	{
		printf("%d : %d\n", count, traceCpus[count]);
	}
}
