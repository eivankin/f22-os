#include <stdio.h>
#include <stdlib.h>


#define ARR_SIZE 5

#define cast_and_apply(type, op) \
type *result = malloc(sizeof(type)); \
*result = (*(type*) a op *(type*)b); \
return (void *) result

#define aggr_with_type(type) \
output = malloc(sizeof(type)); \
*((type *) output) = (type) *(int *) initial_value; \
for (size_t i = 0; i < n; ++i) { \
    output = opr(output, &((type *)base)[i]); \
}                            \
if (opr == meanInt || opr == meanDouble) {    \
    *((type *) output) = *((type *) output) / n; \
}

#define apply(type, init, func) aggregate(type ## s, sizeof(type), ARR_SIZE, init, func)

void *aggregate(void *base, size_t size, int n, void *initial_value, void *(*opr)(const void *, const void *));

void *addInt(const void *a, const void *b) {
    cast_and_apply(int, +);
}

void *addDouble(const void *a, const void *b) {
    cast_and_apply(double, +);
}

void *mulInt(const void *a, const void *b) {
    cast_and_apply(int, *);
}

void *mulDouble(const void *a, const void *b) {
    cast_and_apply(double, *);
}

void *meanInt(const void *a, const void *b) {
    cast_and_apply(int, +);
}

void *meanDouble(const void *a, const void *b) {
    cast_and_apply(double, +);
}

void *aggregate(void *base, size_t size, int n, void *initial_value, void *(*opr)(const void *, const void *)) {

    void *output;

    if (size == sizeof(int)) { // base is a pointer to an integer
        aggr_with_type(int)

    } else { // base is a pointer to a double
        aggr_with_type(double)
    }

    return output;
}


int main() {

    int ints[ARR_SIZE] = {1, 2, 3, 4, 5};
    double doubles[ARR_SIZE] = {3.14, 0.5, 8.08, 1.1, 10};

    int *initial_value = malloc(sizeof(int));

    // Addition
    *initial_value = 0;

    int *result1a = apply(int, initial_value, addInt);
    printf("%d\n", *result1a);

    double *result2a = apply(double, initial_value, addDouble);
    printf("%f\n", *result2a);

    // Multiplication
    *initial_value = 1;

    int *result1m = apply(int, initial_value, mulInt);
    printf("%d\n", *result1m);

    double *result2m = apply(double, initial_value, mulDouble);
    printf("%f\n", *result2m);

    // Mean
    *initial_value = 0;

    int *result1mean = apply(int, initial_value, meanInt);
    printf("%d\n", *result1mean);

    double *result2mean = apply(double, initial_value, meanDouble);
    printf("%f\n", *result2mean);


    free(initial_value);

    return EXIT_SUCCESS;
}

