#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define END_STR "\n"
#define SEPARATOR ", "
#define EOL '\n'

unsigned count(char str[], char chrToSearch) {
	unsigned result = 0;
	for (int i = 0; i < strlen(str); ++i) {
		if (tolower(str[i]) == chrToSearch)
			++result;
	}
	return result;
}

void countAll(char str[]) {
	unsigned len = strlen(str);
	for (int i = 0; i < len; ++i) {
		char chrToSearch = tolower(str[i]);
		printf("%c:%u", chrToSearch, count(str, chrToSearch));
		printf((i + 1 < len) ? SEPARATOR : END_STR);
	}	
}

int main() {
	char buff[257];
	fgets(buff, 256, stdin);
	sscanf(buff, "%s", buff); // trim string
	countAll(buff);
}
