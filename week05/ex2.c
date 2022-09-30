#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 256
#define THREAD_MSG "Hello from thread %u"
#define MAIN_MSG "Thread %u is created\n"

typedef struct {
    pthread_t id;
    int i;
    char message[MSG_SIZE];
} Thread;

void *hello_from(void *arg) {
    Thread *thread = (Thread *) arg;
    printf("Thread #%lu: %s\n", thread->id, thread->message);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    unsigned numberOfThreads;

    if (argc < 2 || sscanf(argv[1], "%u", &numberOfThreads) < 1) {
        printf("Failed to parse the number of threads.\n");
        return EXIT_FAILURE;
    }

    Thread threads[numberOfThreads];
    for (unsigned i = 0; i < numberOfThreads; ++i) {
        threads[i].i = i;
        sprintf(threads[i].message, THREAD_MSG, i);
        int status = pthread_create(&threads[i].id, NULL,
                                    hello_from, (void *) &threads[i]);
        if (status != 0) {
            printf("Failed to create a new thread: %s\n", strerror(status));
        }

        printf(MAIN_MSG, i);
        pthread_join(threads[i].id, NULL);
    }

    return EXIT_SUCCESS;
}