#include <stdint.h>
#include <pthread.h>

int32_t semaphore_createPseudoFileSemaphore(void);
void    semaphore_deletePseudoFileSemaphore(void);
int32_t semaphore_openPseudoFile(int* fileDescriptor,
		                         const char* processDescriptor,
					             int mode,char* function);
int32_t semaphore_closePseudoFile(int fileDescriptor, char* function);
int32_t semaphore_lockQnxSemaphore(char* function);
void    semaphore_unlockQnxSemaphore(char* function);
