#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    double x;
    double y;
} Point;

float distance(Point A, Point B) {
    return sqrt(pow(A.x - B.x, 2) +
                pow(A.y - B.y, 2));
}

float area(Point A, Point B, Point C) {
    return fabs(
            A.x * B.y - B.x * A.y + B.x * C.y -
            C.x * B.y + C.x * A.y - A.x * C.y
    ) / 2;
}

int main(void) {

    struct Point A = {2.5, 6}, B = {1, 2.2}, C = {10, 6};

    float f = distance(A, B);
    printf("A -- B distance is %f\n", f);


    float a = area(A, B, C);
    printf("Area of triangle ABC is %f\n", a);

    return EXIT_SUCCESS;
}
