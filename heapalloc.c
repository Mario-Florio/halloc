#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "heapalloc.h"

#define CAPACITY 640000
char bitmap[CAPACITY] = { 0 * CAPACITY };

typedef struct {
    void* start;
    int free_space;
} Heap;

static Heap heap;

static void throwerror(char* name);
static int getsmallestfreespace(size_t size);

static void heapinit() {
    void* address_space = mmap(NULL, CAPACITY,
                               PROT_READ|PROT_WRITE,
                               MAP_PRIVATE|MAP_ANONYMOUS,
                               0, 0);

    if (address_space == MAP_FAILED) throwerror("mmap");

    heap.start = address_space;
    heap.free_space = CAPACITY;
}

void* heapalloc(size_t size) {
    if (size > 127) throwerror("Sizes greater than 127 bits not supported");
    if (heap.start == NULL) heapinit();
    if (size > heap.free_space) throwerror("Reached max heap capacity");
    if (size < 1) throwerror("Must request size greater than 0");

    int start = getsmallestfreespace(size);

    if (start == -1) throwerror("Unable to fulfill request");

    for (int i = start; i < start+size; i++) {
        bitmap[i] = 1;
    }
    bitmap[start] = size;

    void* mem_address = (void*)heap.start+start;
    heap.free_space -= size;

    return mem_address;
}

void heapfree(void* ptr) {
    int chunk_size = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (heap.start+i == ptr) {
            chunk_size = bitmap[i];
            int j = i;
            while (j < chunk_size+i) {
                bitmap[j] = 0;
                j++;
            }
            break;
        }
    }

    if (chunk_size == 0) throwerror("Memory address is already free");
    
    heap.free_space += chunk_size;
}

// UTILS
static void throwerror(char* name) {
    perror(name);
    exit(1);
}

static int getsmallestfreespace(size_t size) {
    int curr_idx = 0, curr_space = 0, found = 0;
    int smallest_idx = 0, smallest_space = CAPACITY+1;

    for (int i = 0; i < CAPACITY+1; i++) {
        if (curr_space == size) found = 1;
        if (smallest_space == size) break;
        if (bitmap[i] == 0) {
            curr_space++;
        } else {
            if (curr_space >= size && curr_space < smallest_space) {
                smallest_space = curr_space;
                smallest_idx = curr_idx;
            }
            curr_idx = i+1;
            curr_space = 0;
        }
    }

    // used in cases where "else" block doesn't run
    if (curr_space >= size && curr_space < smallest_space) {
        smallest_space = curr_space;
        smallest_idx = curr_idx;
    }

    return found ? smallest_idx : -1;
}
