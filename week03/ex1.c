#include <stdio.h>
#include <stdlib.h>

#define CURR_YEAR 2022
#define ARRAY_SIZE 5

int foo(int age) {
    return CURR_YEAR - age;
}

void print_array(const int *const array) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d\n", array[i]);
    }
}

int main() {
    const int x = 10;
    const int *q = &x; // useless

    const int *const p = malloc(ARRAY_SIZE * sizeof(int));

    printf("Cell addresses:\n");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        ((int *) p)[i] = x;
        printf("%p\n", &p[i]);
    }

    printf("\nEnter ages of students: ");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", (int *) &p[i]);
    }

    printf("\nAges of students:\n");
    print_array(p);

    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        ((int *) p)[i] = foo(p[i]);
    }

    printf("\nBirth years of students:\n");
    print_array(p);

    free((int *) p);
    return EXIT_SUCCESS;
}