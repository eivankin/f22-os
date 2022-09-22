#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

double toMillis(long ticks) {
    return (double) (1000 * ticks) / CLOCKS_PER_SEC;
}

int main() {
    pid_t firstChild, secondChild;

    printf("Main process PID: %d\n", getpid());
    firstChild = fork();
    if (firstChild) {
        printf("First child PID: %d\n", firstChild);

        secondChild = fork();

        if (secondChild) {
            printf("Second child PID: %d\n", secondChild);
            printf("Parent of the main process PID: %d, time consumed (ms): %f\n", getppid(), toMillis(clock()));
            while (wait(NULL) > 0);
        } else {
            printf("Parent of the second child PID: %d, time consumed (ms): %f\n", getppid(), toMillis(clock()));
        }
    } else {
        printf("Parent of the first child PID: %d, time consumed (ms): %f\n", getppid(), toMillis(clock()));
    }

    return EXIT_SUCCESS;
}