#include <stdio.h>
#include <stdlib.h>

int hvad(unsigned int n) {
	return n & n<<1 & n<<2;
}

int main() {
	hvad(1);
	return 0;
}
