#include "../utils/test/test.h"

void heapinit_tests();
void heapalloc_tests();
void heapfree_tests();

void heap_testsuites() {
    suite("HEAP INIT TESTS", heapinit_tests);
    suite("HEAP ALLOC TESTS", heapalloc_tests);
    suite("HEAP FREE TESTS", heapfree_tests);
}

void heapinit_tests() {

    it("Works!", 1);
    it("Doesn't work :(", 0);
}

void heapalloc_tests() {
    it("Works!", 1);
    it("Doesn't work :(", 0);
}

void heapfree_tests() {
    it("Works!", 1);
    it("Doesn't work :(", 0);
}
