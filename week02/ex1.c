#include <stdio.h>
#include <limits.h>
#include <float.h>

#define printValAndSize(fmt, num) printf(fmt, num, sizeof(num))

int main() {
	int intMax = INT_MAX;
	unsigned short ushortMax = USHRT_MAX;
	long int longMax = LONG_MAX;
	float floatMax = FLT_MAX;
	double doubleMax = DBL_MAX;

	printValAndSize("Value of INT_MAX: %d, size: %ld\n", intMax);
	printValAndSize("Value of USHRT_MAX: %u, size: %ld\n", ushortMax);
	printValAndSize("Value of LONG_MAX: %ld, size: %ld\n", longMax);
	printValAndSize("Value of FLT_MAX: %e, size: %ld\n", floatMax);
	printValAndSize("Value of DBL_MAX: %e, size: %ld\n", doubleMax);
}
