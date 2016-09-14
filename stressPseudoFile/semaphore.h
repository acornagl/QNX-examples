#include <stdint.h>
#include <pthread.h>

int32_t semaphore_createPseudoFileSemaphore(void);
void    semaphore_deletePseudoFileSemaphore(void);
int32_t semaphore_openPseudoFile(int* fileDescriptor,
		                         const char* processDescriptor,
					             int mode);
int32_t semaphore_closePseudoFile(int fileDescriptor);
int32_t semaphore_lockQnxSemaphore(void);
void    semaphore_unlockQnxSemaphore(void);
