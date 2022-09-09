#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h> 

#define screamAndDie printf("cannot convert!"); exit(1);


bool isBaseValid(unsigned base) {
	return base >= 2 && base <= 10;
}


unsigned convertFrom10OrTo10(unsigned num, unsigned from, unsigned to) {
	unsigned result = 0, pos = 0;
	while (num > 0) {
		unsigned short digit = num % to;
		if (digit >= from) {
			screamAndDie
		}
		result += digit * pow(from, pos);
		++pos;
		num /= to;
	}
	return result;
}

unsigned convert(unsigned num, unsigned from, unsigned to) {
          if (isBaseValid(from) && isBaseValid(to)) {
                return convertFrom10OrTo10(convertFrom10OrTo10(num, from, 10), 10, to);
          }
	  screamAndDie
}


int main() {
	unsigned inputNum, fromBase, toBase;
	scanf("%u %u %u", &inputNum, &fromBase, &toBase);
	printf("%u", convert(inputNum, fromBase, toBase));
}
