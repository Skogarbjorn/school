#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
	int inntala;

	while (scanf("%d", &inntala) != EOF) {
		printf("%d\n", inntala + atoi(argv[1]));
	}

	return 0;
}
