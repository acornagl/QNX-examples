#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/procfs.h>
#include <errno.h>
#include <fcntl.h>

void* threadBodies_readBody(void* ptr);

void* threadBodies_writeBody(void* ptr);

void* threadBodies_openPseudo1(void* ptr);

void* threadBodies_callPid(void* ptr);

void threadBodies_freePseudoFile(void);

void threadBodies_printVisitedCPUs(void);

