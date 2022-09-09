#include <stdio.h>

#define ul unsigned long

ul tribonacci(unsigned n) {
	ul t0 = 0, t1 = 1, t2 = 1;
	if (n == 0)
		return t0;
	for (int i = 2; i < n; ++i) {
		ul tmp = t2;
		t2 = t0 + t1 + t2;
		t0 = t1;
		t1 = tmp;	
	}

	return t2;
}

int main() {
	printf("%lu\n", tribonacci(4));
	printf("%lu", tribonacci(36));	
}
