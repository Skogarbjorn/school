#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv ) {
	int count = 0;
	for ( int i = 1; i < argc; i++ ) {
		count += strlen(argv[i]); 
	}

	char *cat = (char *)calloc(count, sizeof(char));

	for ( int i = 1; i < argc; i++ ) {
		strcat(cat, argv[i]);
	}

	printf("Length is: %i\n", count);
	printf("Concatenation: %s\n", cat);
	return 0;
}
