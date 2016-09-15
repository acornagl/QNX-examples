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
pthread_t t1, t2;

/******************************************************************************/

int main()
{
//	(void) pthread_create(&t1, NULL, readBody,  (void*) NULL);
//	(void) pthread_create(&t2, NULL, writeBody, (void*) NULL);

	// Create the semaphore in a thread-safe way (at the present moment the
	// main is the only thread)
    int32_t result = semaphore_createPseudoFileSemaphore();
    printf("[MAIN] semaphore_createPseudoFileSemaphore(): %d\n", result);

    (void) pthread_create(&t1, NULL, threadBodies_readBody,  (void*) NULL);
    (void) pthread_create(&t2, NULL, threadBodies_writeBody, (void*) NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    threadBodies_printVisitedCPUs();
    // Clean-up
    semaphore_deletePseudoFileSemaphore();
    threadBodies_freePseudoFile();

	return 0;
}

/**
 * COMPILATION
 * export QNX_HOST=/tools/cross/qnx/momentics-6.5/host/linux/x86
 * export QNX_TARGET=/tools/cross/qnx/momentics-6.5/target/qnx6/
 *
 * /tools/cross/qnx/momentics-6.5/host/linux/x86/usr/bin/ntox86-gcc -DFD_SETSIZE=1024  -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D__LCMS_LITTLE_ENDIAN -D_LITTLE_ENDIAN -DMP_API_COMPATIBLE -DNSS_ECC_MORE_THAN_SUITE_B -gdwarf-2  -mtune=pentium -march=pentium -DLE_STANDALONE -DHEADLESS *.c -o stressPseudoFiles
 */
