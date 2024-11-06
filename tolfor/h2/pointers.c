#include <stdio.h>

int main() {
	int i = 4;
	int* p = &i;
	int* q = NULL;
	int** t = &q;
	*t = &i;
	**t = 8;

	printf("i is %i, p is %i, q is %i, t is %i\n", i, *p, *q, **t);
	return 0;
}
