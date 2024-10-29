#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "heapalloc.h"
#include "bitmap.h"

typedef struct {
    void* heap;
    int freedspace;
} Heapdata;

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

    #ifdef DEBUGGER
        PRINTBITMAP("HEAP INIT", bitmap);
    #endif
}

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

    int start = 0, freewindow = 0, found = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (freewindow == size) {
            found = 1;
        }

        if (bitmap[i] == 0) {
            freewindow++;
        } else {
            freewindow = 0;
            start = i+1;
        }
    }

    if (!found) {
        perror("Unable to fulfill request");
        exit(1);
    }

    for (int i = start; i < start+size; i++) {
        bitmap[i] = 1;
    }
    bitmap[start] = size;

    void* memaddress = (void*)heapdata.heap+start;
    heapdata.freedspace -= size;

    #ifdef DEBUGGER
        PRINTBITMAP("HEAP ALLOC", bitmap);
    #endif

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

    #ifdef DEBUGGER
        PRINTBITMAP("HEAP FREE", bitmap);
    #endif

    heapdata.freedspace += chunksize;
}