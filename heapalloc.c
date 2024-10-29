#include "heapalloc.h"

#define CAPACITY 640000

typedef struct {
    void* heap;
    int freedspace;
} Heapdata;

char bitmap[CAPACITY] = {  0 * CAPACITY };

static Heapdata heapdata;

void* heapalloc(size_t size) {

    return 0;
}

void heapfree(void* ptr) {
    
}
