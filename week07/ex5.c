#include <stdio.h>
#include <stdlib.h>

int main() {
    char **s;
    char foo[] = "Hello World";
    s = malloc(1 * sizeof(char)); // initialize variable s
    *s = foo;
    printf("s is %p\n", s); // change print type to pointer
    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    free(s); // free pointer
    return EXIT_SUCCESS;
}