#include <stdio.h>

void printbitmap(char* title, char* bitmap, int capacity) {
    printf("%s\n", title);
    for (int i = 0; i < capacity; i++) {
        printf("%d ", bitmap[i]);
    }
    printf("\n");
}
