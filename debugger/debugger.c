#include <stdio.h>

void printbitmap(char* title, char* bitmap) {
    printf("%s\n", title);
    for (int i = 0; i < sizeof(bitmap); i++) {
        printf("%d ", bitmap[i]);
    }
    printf("\n");
}
