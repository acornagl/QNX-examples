/**
 * Copyright (c) 2016 Alessandro Cornaglia
 * Licensed under the MIT license.
 */

#include <stdio.h>
#include <pthread.h>

/**************************** MACROS AND CONSTANTS ****************************/


/********************************* VARIABLES **********************************/
pthread t1, t2;

/********************************* FUNCTIONS **********************************/

/********************************* PROCEDURES**********************************/

/******************************************************************************/

int main() {

	printf("[main] Start the main program\n");

	(void) pthread_create(&t1, NULL, simpleThreadBody, (void*) NULL);
	(void) pthread_create(&t2, NULL, setAffinityBody , (void*) NULL);
	printf("[main] created threads t1 and t2 \n");

	pthread_join(t1, NULL);
	printf("[main] t1 joined\n");
	pthread_join(t2, NULL);
	printf("[main] t2 joined\n");


	return 0;
}
