#include <stdio.h>

#define TERMINAL_CHAR '.'
#define EOL '\n'
#define QUOTE '"'

void readAndPrintUntil() {
	// Recursion is more beautiful than C arrays
	char input = getchar();
	if (input == TERMINAL_CHAR || input == EOL) {
		putchar(QUOTE);
		return;
	}
	readAndPrintUntil();
	putchar(input);
}

int main() {
	readAndPrintUntil();
	putchar(QUOTE);
}
