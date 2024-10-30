#include "../utils/test/test.h"
#include "../heapalloc.h"
#include "../bitmap/bitmap.h"

void heapalloc_tests();
void heapfree_tests();

void heap_testsuites() {
    suite("HEAP ALLOC TESTS", heapalloc_tests);
    suite("HEAP FREE TESTS", heapfree_tests);
}

void heapalloc_tests() {
    char* bitmap = getbitmap();

    heapalloc(sizeof(char) * 2);
    it("Allocates to appropriate place on bitmap", bitmap[0] != 0 && bitmap[1] != 0);
    heapalloc(sizeof(int));
    heapalloc(sizeof(char) * 2);
    it("Sets value of first bit of allocated to chunk to requested size", bitmap[6] == 2);
}

void heapfree_tests() {
    it("Works!", 1);
    it("Doesn't work :(", 0);
}
