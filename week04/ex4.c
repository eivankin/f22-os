#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 256
#define EXIT_COMMAND "exit\n"

void input(char *word) {
    printf(">>> ");
    if (!fgets(word, INPUT_SIZE, stdin))
        exit(EXIT_SUCCESS);
}

int main() {
    printf("Enter 'exit' to exit the shell\n");

    char word[INPUT_SIZE];
    do {
        input(word);
        // No need for forks and execve
        system((const char *) &word);
    }
    while (strcmp(word, EXIT_COMMAND) != 0);
    return EXIT_SUCCESS;
}