#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "ex1_commons.h"

int main(int argc, char* argv[]) {
    int numberOfSubscribers = 1;

    if (argc > 1) {
        int processed = sscanf(argv[1], "%d", &numberOfSubscribers);

        if (processed < 1) {
            printf("Failed to parse the number of subscribers\n");
            return EXIT_FAILURE;
        }

        if (numberOfSubscribers < 1) {
            printf("Number of subscribers must be greater than 0.\n");
            return EXIT_FAILURE;
        }
    }

    // check if pipe exists, otherwise create it with mkfifo
    if (access(PIPE_NAME, F_OK) != 0 && mkfifo(PIPE_NAME, S_IRWXU) == -1) {
        printf("Failed to create the pipe: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    FILE *pipe = fopen(PIPE_NAME, "w");
    char messageBuffer[MSG_SIZE];

    if (pipe != NULL) {
        while (1) {
            printf("Enter the message: ");
            if (fgets(messageBuffer, MSG_SIZE, stdin) == NULL)
                break;

            for (int i = 0; i < numberOfSubscribers; ++i) {
                fprintf(pipe, "%s", messageBuffer);
                fflush(pipe);
                usleep(100000); // 0.1 seconds
            }
        }
    } else {
        printf("Failed to open the pipe: %s\n", strerror(errno));
    }
    return EXIT_SUCCESS;
}