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

    void* mem1 = heapalloc(sizeof(char) * 2);
    it("Allocates to appropriate place on bitmap", bitmap[0] != 0 && bitmap[1] != 0);
    void* mem2 = heapalloc(sizeof(int));
    void* mem3 = heapalloc(sizeof(char) * 2);
    it("Sets value of first bit of allocated to chunk to requested size", bitmap[6] == 2);

    heapfree(mem1);
    heapfree(mem2);
    heapfree(mem3);
}

void heapfree_tests() {
    char* bitmap = getbitmap();

    void* mem1 = heapalloc(sizeof(char) * 2);
    void* mem2 = heapalloc(sizeof(int));

    heapfree(mem2);
    it("Frees accurate memory bits", bitmap[2] == 0 && bitmap[3] == 0 &&
                                     bitmap[4] == 0 && bitmap[5] == 0);

    heapfree(mem1);
}
