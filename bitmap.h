#ifndef heapalloc_bitmap_bitmap_h
#define heapalloc_bitmap_bitmap_h

#include "build.h"

#ifdef DEBUGGER
    #include "utils/debugger/debugger.h"

    #define CAPACITY 20
    #define PRINTBITMAP(TITLE, BITMAP) printbitmap(TITLE, BITMAP, CAPACITY)
#else
    #define CAPACITY 640000
#endif

char bitmap[CAPACITY] = { 0 * CAPACITY };

#endif