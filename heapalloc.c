#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "heapalloc.h"

#define CAPACITY 640000

typedef struct {
    void* heap;
    int freedspace;
} Heapdata;

char bitmap[CAPACITY] = {  0 * CAPACITY };

static Heapdata heapdata;

static void heapinit() {
    void* address_space = mmap(NULL, CAPACITY,
                          PROT_READ|PROT_WRITE,
                          MAP_PRIVATE|MAP_ANONYMOUS,
                          0, 0);

    if (address_space == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    heapdata.heap = address_space;
    heapdata.freedspace = CAPACITY;
}

void* heapalloc(size_t size) {

    return 0;
}

void heapfree(void* ptr) {
    
}
