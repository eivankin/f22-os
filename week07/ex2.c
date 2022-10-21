#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t arraySize;
    printf("Enter the array size: ");
    if (scanf("%zu", &arraySize) < 1) {
        printf("Failed to parse the array size.\n");
        return EXIT_FAILURE;
    }

    if (arraySize < 1) {
        printf("Array size must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(arraySize * sizeof(int));

    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < arraySize; ++i) {
        array[i] = i;
    }

    printf("Array contents: ");
    for (int i = 0; i < arraySize; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return EXIT_SUCCESS;
}