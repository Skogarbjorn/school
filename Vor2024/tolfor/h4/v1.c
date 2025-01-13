#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 5, y;
	x *= y = 2;
	x = y == 2;
	x == (y = 3);
	x = (unsigned)-3 > 0 ? y << 1 : y >> 1;

	printf("%i", x);
	printf("%i", y);
	return 0;
}
