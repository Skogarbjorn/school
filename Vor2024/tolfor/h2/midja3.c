#include <stdio.h>
#include <stdlib.h>

int min( int a, int b ) {
	return a < b ? a : b;
}
int max( int a, int b ) {
	return a > b ? a : b;
}

//int main( int argc, char *argv[] ) {
//	int gamer[argc-1];
//	for (int i=0; i < argc-1; i++) {
//		gamer[i] = atoi(argv[i+1]);
//	}
//	int l = min(min(gamer[0],gamer[1]),gamer[2]);
//	int h = max(max(gamer[0],gamer[1]),gamer[2]);
//	int mid = gamer[0] + gamer[1] + gamer[2] - l - h;
//
//	printf("%i\n", mid);
//	return 0;
//}

int main( int argc, char *argv[]) {
	int i, j, k;
	
	if (argc > 3) {
		i = atoi(argv[1]);
		j = atoi(argv[2]);
		k = atoi(argv[3]);
	} else {
		printf("Too few arguments, please input 3 numbers.\n");
		exit(0);
	}

	int m = i < j ? i > k ? i : j < k ? j : k : i < k ? i : j < k ? k : j;
	printf("Miðgildi: %d\n", m);

	return 0;
}
