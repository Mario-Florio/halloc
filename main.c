#include <stdio.h>

#include "build.h"

#ifdef TEST
    #include "testsuites/testsuites.h"

    #define RUN_TESTS() heap_testsuites()
#else
    #define RUN_TESTS() printf("Define TEST in build.h to run tests\n");
#endif

int main(int argc, char** argv) {
    RUN_TESTS();
    
    return 1;
}
