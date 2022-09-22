#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    unsigned numberOfForks;
    if (argc == 2) {
        sscanf(argv[1], "%d", &numberOfForks);

        for (unsigned i = 0; i < numberOfForks; ++i) {
            fork();
            sleep(5);
        }
    }
    return EXIT_SUCCESS;

}
