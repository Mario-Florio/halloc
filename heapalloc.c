#include "heapalloc.h"

typedef struct {
    void* heap;
    int freedspace;
} Heapdata;

static Heapdata heapdata;

void* heapalloc(size_t size) {

    return 0;
}

void heapfree(void* ptr) {
    
}
