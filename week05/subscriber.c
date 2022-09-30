#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "ex1_commons.h"

int main() {
    FILE *pipe = fopen(PIPE_NAME, "r");
    char messageBuffer[MSG_SIZE];

    printf("Subscriber #%d\n", getpid());

    if (pipe != NULL) {
        while (1) {
            if (fgets(messageBuffer, MSG_SIZE, pipe) == NULL) {
                return EXIT_SUCCESS; // stop if publisher stopped
            }
            printf("Received: %s", messageBuffer);
        }
    } else {
        printf("Failed to open the pipe: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
}