#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ex1_commons.h"

#define READ_END pipeDescriptors[0]
#define WRITE_END pipeDescriptors[1]

FILE *open_pipe(int fd, const char *modes) {
    FILE *pipe = fdopen(fd, modes);
    if (pipe == NULL) {
        printf("Failed to open the pipe: %s\n", strerror(errno));
    }
    return pipe;
}

pid_t fork_or_die() {
    pid_t childPid = fork();
    if (childPid == -1) {
        printf("Failed to create a child process: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return childPid;
}

int main() {
    int pipeDescriptors[2];

    if (pipe(pipeDescriptors) == -1) {
        printf("Failed to create a new pipe: %s\n", strerror(errno));
    }

    pid_t childPid = fork_or_die();
    char messageBuffer[MSG_SIZE];
    FILE *pipe;

    if (childPid == 0) {
        // subscriber
        close(WRITE_END);

        pipe = open_pipe(READ_END, "r");

        if (fgets(messageBuffer, MSG_SIZE, pipe) == NULL) {
            return EXIT_SUCCESS; // stop if publisher stopped
        }
        printf("Received by subscriber #%d: %s", getpid(), messageBuffer);
        close(READ_END);
        exit(EXIT_SUCCESS);
    } else {
        // I'll use the main process as a publisher instead of forking twice
        // since the main process is not used anymore.
        close(READ_END);

        pipe = open_pipe(WRITE_END, "w");

        printf("Enter the message: ");
        fgets(messageBuffer, MSG_SIZE, stdin);

        fprintf(pipe, "%s", messageBuffer);
        fflush(pipe);
        close(WRITE_END);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}