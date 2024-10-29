#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void suite(char* name, void (*func)()) {
    printf("%s\n", name);
    func();
}

void it(char* name, int condition) {
    if (condition) {
        printf("\033[1;32m"); // green
        printf("    ");
        printf("%s", name);
        printf(" ✓\n");
    } else {
        printf("\033[1;31m"); // red
        printf("    ");
        printf("%s", name);
        printf(" ✗\n");
    }

    printf("\033[1;0m");
}
