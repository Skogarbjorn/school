#include <stdio.h>

short int a = 2;
short int b = 8;
extern short int c;

void fun() {
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	printf("c: %d\n", c);
}
