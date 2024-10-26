#ifndef heapalloc_heapalloc_h
#define heapalloc_heapalloc_h

#include <stddef.h>

void* heapalloc(size_t size);
void heapfree(void* ptr);

#endif