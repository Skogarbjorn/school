#include <stdio.h>
#include <stdlib.h>


unsigned long sammengi(unsigned long a, unsigned long b) {
	return a | b;
}

unsigned long munur(unsigned long a, unsigned long b) {
	return a & ~b;
}

int stakI(unsigned long a, int i) {
	return (a & (1ul << i)) > 0;
}

int main() {
	long x = 1ul << 3;
	// 2^i
	printf("%i\n", x);

	int gamer = stakI(16, 4);
	printf("%i", gamer);
	return 0;
}
