#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 5;
	int *p = (int *)malloc(sizeof(int));
	int *q = &i;
	*p = *q;
	q = p;

	printf("i is %i", i);
	printf("p points to %i", *p);
	printf("p is %i", p);
	printf("q points to %i", *q);
	printf("q is %i", q);
	printf("\n reference value to i is %i", &i);
	return 0;
}
