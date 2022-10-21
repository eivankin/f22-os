#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void *myRealloc(void *ptr, size_t size) {
    void *newPtr = malloc(size);
    if (ptr != NULL) {
        memcpy(newPtr, ptr, size);
        free(ptr);
    }
    return newPtr;
}

// Code from previous exercise to check if realloc works correctly
int main() {
    // Allows user to specify the original array size, stored in variable n1.
    printf("Enter original array size: ");
    int n1 = 0;
    scanf("%d", &n1);

    //Create a new array of n1 ints
    int *a1 = malloc(n1 * sizeof(int));
    if (a1 == NULL && n1 != 0) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    int i;
    if (a1 != NULL) {
        for (i = 0; i < n1; i++) {
            //Set each value in a1 to 100
            a1[i] = 100;

            //Print each element out (to make sure things look right)
            printf("%d ", a1[i]);
        }
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2);

    //Dynamically change the array to size n2
    a1 = realloc(a1, n2 * sizeof(int));
    if (a1 == NULL && n2 != 0) {
        perror("realloc");
        return EXIT_FAILURE;
    }

    if (a1 != NULL) {
        //If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.
        if (n2 > n1) {
            for (i = n1; i < n2; i++) {
                a1[i] = 0;
            }
        }


        for (i = 0; i < n2; i++) {
            //Print each element out (to make sure things look right)
            printf("%d ", a1[i]);
        }
        printf("\n");

        free(a1);
    }

    //Done with array now, done with program :D

    return EXIT_SUCCESS;
}
