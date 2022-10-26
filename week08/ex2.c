#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NUM_ITER 10
#define SIZE 10485760 // 10 MB

/**
 * During the execution, amount of free memory slowly decreasing.
 * 'si' and 'so' fields contains only zeros, no swap space is used.
 *
 * 'top' command shows the same result.
 */

int main() {
    int **arrays = malloc(sizeof(int*) * NUM_ITER);
    for (int i = 0; i < NUM_ITER; ++i) {
        arrays[i] = malloc(SIZE);
        if (arrays[i] != NULL) {
            memset(arrays[i], 0, SIZE);
            sleep(1);
        } else {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_ITER; ++i) {
        free(arrays[i]);
    }
    free(arrays);

    return EXIT_SUCCESS;
}
