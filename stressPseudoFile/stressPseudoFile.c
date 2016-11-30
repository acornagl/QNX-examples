/**
 * Copyright (c) 2016 Alessandro Cornaglia
 * Licensed under the MIT license.
 */
#include "semaphore.h"
#include "threadBodies.h"

#include <stdio.h>
#include <pthread.h>
#include <devctl.h>
#include <stdint.h>
#include <fcntl.h>



/******************************** VARIABLES ***********************************/
pthread_t t0;
pthread_t t1, t2;
pthread_t t3, t4;
pthread_t t5, t6;
pthread_t t7, t8;
pthread_t t9, t10;
pthread_t t11, t12;

pthread_t t13, t14, t15, t16;
/******************************************************************************/

int main()
{
//	(void) pthread_create(&t1, NULL, readBody,  (void*) NULL);
//	(void) pthread_create(&t2, NULL, writeBody, (void*) NULL);

	// Create the semaphore in a thread-safe way (at the present moment the
	// main is the only thread)
/*    int32_t result = semaphore_createPseudoFileSemaphore();
    printf("[MAIN] semaphore_createPseudoFileSemaphore(): %d\n", result);

    (void) pthread_create(&t0, NULL, threadBodies_openPseudo1,  (void*) NULL);
    (void) pthread_create(&t1, NULL, threadBodies_readBody,  (void*) NULL);
    (void) pthread_create(&t2, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t3, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t4, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t5, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t6, NULL, threadBodies_writeBody, (void*) NULL);

    (void) pthread_create(&t7, NULL, threadBodies_readBody,  (void*) NULL);
    (void) pthread_create(&t8, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t9, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t10, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t11, NULL, threadBodies_writeBody, (void*) NULL);
    (void) pthread_create(&t12, NULL, threadBodies_writeBody, (void*) NULL);

    (void) pthread_create(&t13, NULL, threadBodies_callPid, (void*) NULL);
    (void) pthread_create(&t14, NULL, threadBodies_callPid, (void*) NULL);
    (void) pthread_create(&t15, NULL, threadBodies_callPid, (void*) NULL);
    (void) pthread_create(&t16, NULL, threadBodies_callPid, (void*) NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);

    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
    pthread_join(t9, NULL);
    pthread_join(t10, NULL);
    pthread_join(t11, NULL);
    pthread_join(t12, NULL);

    pthread_join(t13, NULL);
    pthread_join(t14, NULL);
    pthread_join(t15, NULL);
    pthread_join(t16, NULL);

    threadBodies_printVisitedCPUs();
    // Clean-up
    semaphore_deletePseudoFileSemaphore();
    threadBodies_freePseudoFile();
*/

#define open open64
	printf("[pthread_self]: %d\n", pthread_self());
	printf("[getpid()]: %d\n", getpid());
	printf("[shm_open()]: %d\n",shm_open("hello",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR));
	struct stat statbuf;
	printf("[stat()]: %d\n",stat("/proc", &statbuf));
	procfs_mapinfo mapinfo[1];
	int nmembuf;
	printf("[devctl(DCMD_PROC_PAGEDATA)]: %d\n",devctl(1, DCMD_PROC_PAGEDATA, mapinfo, sizeof(mapinfo), &nmembuf));
	printf("[__tls()->__tid]: %d\n",__tls()->__tid);
	procfs_status status;
    status.tid = __tls()->__tid;
	printf("[_devctl(DCMD_PROC_TIDSTATUS)]: %d\n",_devctl(1, DCMD_PROC_TIDSTATUS, &status, sizeof(status), 0));
	struct _debug_process_info process_info;
	printf("[devctl(DCMD_PROC_INFO)]: %d\n",devctl(1, DCMD_PROC_INFO, &process_info, sizeof(process_info), NULL));
	return 0;
}

/**
 * COMPILATION
 * export QNX_HOST=/tools/cross/qnx/momentics-6.5/host/linux/x86
 * export QNX_TARGET=/tools/cross/qnx/momentics-6.5/target/qnx6/
 *
 * /tools/cross/qnx/momentics-6.5/host/linux/x86/usr/bin/ntox86-gcc -DFD_SETSIZE=1024  -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D__LCMS_LITTLE_ENDIAN -D_LITTLE_ENDIAN -DMP_API_COMPATIBLE -DNSS_ECC_MORE_THAN_SUITE_B -gdwarf-2  -mtune=pentium -march=pentium -DLE_STANDALONE -DHEADLESS *.c -o stressPseudoFiles
 */
