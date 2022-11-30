#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_PATH "input.txt"
#define MAX_LINE_LEN 512
#define MAX_SIZE MAX_LINE_LEN / 2 // in the worst case, we have N one-digit numbers and N-1 spaces
#define read_line fgets(line, MAX_LINE_LEN, inp)
#define DELIM " "
#define vector(n) malloc(n * sizeof(int))
#define matrix(n) malloc(n * sizeof(int*))

size_t read_array(int *array, char* line) {
    size_t pos = 0;
    int val;
    char *p = strtok(line, DELIM);
    while (p != NULL) {
        if (pos >= MAX_SIZE) {
            printf("Array capacity exceeded!\n");
            exit(EXIT_FAILURE);
        }
        sscanf(p, "%d", &val);
        array[pos++] = val;
        p = strtok(NULL, DELIM);
    }
    return pos;
}

size_t num_res;
int *A;
int **R, **C;

bool fits(size_t proc_num) {
    for (size_t i = 0; i < num_res; ++i) {
        if (R[proc_num][i] > A[i])
            return false;
    }
    return true;
}

void free_resources(size_t proc_num) {
    for (size_t i = 0; i < num_res; ++i) {
        A[i] += C[proc_num][i];
    }
}

int main() {
    int *E = vector(MAX_SIZE);
    C = matrix(MAX_SIZE);

    FILE *inp = fopen(INPUT_PATH, "r");
    if (inp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    size_t num_proc = 0;
    char line[MAX_LINE_LEN];
    read_line;
    num_res = read_array(E, line);

    read_line; // skip empty line

    read_line;
    A = vector(num_res);
    read_array(A, line);

    read_line; // skip empty line

    read_line;
    while (line[0] != '\n') {
        C[num_proc] = vector(num_res);
        read_array(C[num_proc++], line);
        read_line;
    }

    R = matrix(num_proc);
    read_line; // skip empty line
    for (size_t i = 0; i < num_proc; ++i) {
        read_line;
        R[i] = vector(num_res);
        read_array(R[i], line);
    }
    fclose(inp);

    bool finished[num_proc];
    size_t num_finished = 0;
    for (size_t i = 0; i < num_proc; ++i) {
        for (size_t j = 0; j < num_proc; ++j) {
            if (!finished[j] && fits(j)) {
                free_resources(j);
                finished[j] = true;
                ++num_finished;
                break;
            }
        }
    }
    if (num_finished < num_proc) {
        printf("%lu processes are deadlocked\n", num_proc - num_finished);
    } else {
        printf("No deadlock is detected\n");
    }

    free(E);
    free(A);
    for (size_t i = 0; i < num_proc; ++i) {
        free(C[i]);
        free(R[i]);
    }
    free(C);
    free(R);

    return EXIT_SUCCESS;
}