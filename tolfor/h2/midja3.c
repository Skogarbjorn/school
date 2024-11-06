#include <stdio.h>
#include <stdlib.h>

int min( int a, int b ) {
	return a < b ? a : b;
}
int max( int a, int b ) {
	return a > b ? a : b;
}

int main( int argc, char *argv[] ) {
	int gamer[argc-1];
	for (int i=0; i < argc-1; i++) {
		gamer[i] = atoi(argv[i+1]);
	}
	int l = min(min(gamer[0],gamer[1]),gamer[2]);
	int h = max(max(gamer[0],gamer[1]),gamer[2]);
	int mid = gamer[0] + gamer[1] + gamer[2] - l - h;

	printf("%i\n", mid);
	return 0;
}

