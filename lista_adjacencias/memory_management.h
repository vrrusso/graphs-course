#ifndef MEMORY_H
#define MEMORY_H
#include<stdlib.h>

void* allocate(size_t s);//!< allocates heap memory of size s
void  deallocate(void ** ptr); //!< deallocates and points to null the pointer (*ptr)

#endif
