#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define NUM_ITER 10
#define SIZE 10485760 // 10 MB

void printRusage(struct rusage *usage) {
    printf("system CPU time used: %ld.%ld\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec);
    printf("maximum resident set size: %ld\n", usage->ru_maxrss);
    printf("integral shared memory size: %ld\n", usage->ru_ixrss);
    printf("integral unshared data size: %ld\n", usage->ru_idrss);
    printf("integral unshared stack size: %ld\n", usage->ru_isrss);
    printf("\n");
}

int main() {
    struct rusage usage;
    int **arrays = malloc(sizeof(int*) * NUM_ITER);
    for (int i = 0; i < NUM_ITER; ++i) {
        arrays[i] = malloc(SIZE);
        if (arrays[i] != NULL) {
            memset(arrays[i], 0, SIZE);
            getrusage(RUSAGE_SELF, &usage);
            printRusage(&usage);
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