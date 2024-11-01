#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "heapalloc.h"

#define CAPACITY 640000

typedef struct {
    void* heap;
    int freedspace;
} Heapdata;

char bitmap[CAPACITY] = { 0 * CAPACITY };

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

static int getSmallestFreeSpace(size_t size);

void* heapalloc(size_t size) {
    if (heapdata.heap == NULL) heapinit();
    if (size > heapdata.freedspace) {
        perror("Reached max heap capacity");
        exit(1);
    }
    if (size < 1) {
        perror("Must request size greater than 0");
        exit(1);
    }

    int start = getSmallestFreeSpace(size);

    if (start == -1) {
        perror("Unable to fulfill request");
        exit(1);
    }

    for (int i = start; i < start+size; i++) {
        bitmap[i] = 1;
    }
    bitmap[start] = size;

    void* memaddress = (void*)heapdata.heap+start;
    heapdata.freedspace -= size;

    return memaddress;
}

void heapfree(void* ptr) {
    int chunksize = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (heapdata.heap+i == ptr) {
            chunksize = bitmap[i]+i;
            int j = i;
            while (j < chunksize) {
                bitmap[j] = 0;
                j++;
            }
            break;
        }
    }

    if (chunksize == 0) {
        perror("Memory address is already free");
        exit(1);
    }
    
    heapdata.freedspace += chunksize;
}

// UTILS
static int getSmallestFreeSpace(size_t size) {
    int currIdx = 0, currSpace = 0, found = 0;
    int smallestIdx = 0, smallestSpace = CAPACITY+1;

    for (int i = 0; i < CAPACITY+1; i++) {
        if (currSpace == size) found = 1;
        if (smallestSpace == size) break;
        if (bitmap[i] == 0) {
            currSpace++;
        } else {
            if (currSpace >= size && currSpace < smallestSpace) {
                smallestSpace = currSpace;
                smallestIdx = currIdx;
            }
            currIdx = i+1;
            currSpace = 0;
        }
    }

    // used in cases where "else" block doesn't run
    if (currSpace >= size && currSpace < smallestSpace) {
        smallestSpace = currSpace;
        smallestIdx = currIdx;
    }

    return found ? smallestIdx : -1;
}
