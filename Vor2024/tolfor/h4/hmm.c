#include <stdio.h>
#include <stdlib.h>

int hmm( unsigned char n ) {
	return (~n) & (~n << 1);
}
int hmm3( unsigned char n ) {
	return (~n) & (~n << 1) & (~n >> 1);
}
int hmm1( unsigned char n ) {
	return (n) & (n << 1);
}

int main() {
	int x = hmm( 0x54 );
	int y = hmm3( 0x58 );
	int z = hmm1( 0x56 );
	printf("%i\n", x);
	printf("%i\n", y);
	printf("%i\n", z);
	return 0;
}


