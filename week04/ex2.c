#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_VAL 100
#define VECTOR_LEN 120
#define FILENAME "temp.txt"


// Calculate the dot product of the vectors u and v from the component [start] till the component [end] exclusively.
int dotprod(int u[], int v[], int start, int end) {

    int result = 0;

    for (int i = start; i < end; i++) {
        result += u[i] * v[i];
    }

    return result;
}

void fillWithValues(int vector[]) {
    for (unsigned i = 0; i < VECTOR_LEN; ++i) {
        vector[i] = rand() % MAX_VAL;
    }
}

void writeNthResult(unsigned index, int result) {
    FILE *output = fopen(FILENAME, "r+b");
    fseek(output, index * sizeof(int), SEEK_SET);
    fwrite(&result, sizeof(int), 1, output);
    fclose(output);
}

int main(void) {
    int firstVector[VECTOR_LEN], secondVector[VECTOR_LEN];
    fillWithValues(firstVector);
    fillWithValues(secondVector);
    FILE *input = fopen(FILENAME, "w");
    fclose(input);

    unsigned short numberOfProcesses;
    printf("Enter the number of processes (even, <=10): ");
    scanf("%hu", &numberOfProcesses);
    int sampleSize = VECTOR_LEN / numberOfProcesses;
    for (unsigned short currentProcess = 0; currentProcess < numberOfProcesses; ++currentProcess) {
        pid_t pid = fork();

        if (pid == 0) {
            writeNthResult(
                    currentProcess,
                    dotprod(firstVector, secondVector,
                            sampleSize * currentProcess, sampleSize * (currentProcess + 1))
            );
            exit(EXIT_SUCCESS);
        }
    }
    while (wait(NULL) > 0);

    input = fopen(FILENAME, "rb");
    int result = 0, results[numberOfProcesses];
    fread(results, sizeof(int), numberOfProcesses, input);
    fclose(input);
    for (unsigned short i = 0; i < numberOfProcesses; ++i) {
        result += results[i];
    }
    printf("Dot product: %d", result);

    return EXIT_SUCCESS;

}
