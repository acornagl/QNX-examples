/**
 * Copyright (c) 2016 Alessandro Cornaglia
 * Licensed under the MIT license.
 */
#include "semaphore.h"

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

    int32_t result = semaphore_createPseudoFileSemaphore();
    printf("- semaphore_createPseudoFileSemaphore(): %d\n", result);

    int fd = -1;
    result = semaphore_openPseudoFile(&fd, "/proc/1/as", O_RDONLY);
    printf("- semaphore_openPseudoFile(): %d\n", result);

    result = semaphore_closePseudoFile(fd);
    printf("- semaphore_closePseudoFile(): %d\n", result);

    semaphore_deletePseudoFileSemaphore();

	return 0;
}

/**
 * COMPILATION
 * export QNX_HOST=/tools/cross/qnx/momentics-6.5/host/linux/x86
 * export QNX_TARGET=/tools/cross/qnx/momentics-6.5/target/qnx6/
 *
 * /tools/cross/qnx/momentics-6.5/host/linux/x86/usr/bin/ntox86-gcc -DFD_SETSIZE=1024  -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D__LCMS_LITTLE_ENDIAN -D_LITTLE_ENDIAN -DMP_API_COMPATIBLE -DNSS_ECC_MORE_THAN_SUITE_B -gdwarf-2  -mtune=pentium -march=pentium -DLE_STANDALONE -DHEADLESS *.c -o stressPseudoFiles
 */
