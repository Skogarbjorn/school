#include <stdio.h>
#include <stdlib.h>

int func4(int a, int b, int c) {
	int x = c - b;
    int y = x;
    y = (unsigned int)y>>31;
    y += x;
    y = (signed int)y>>1;
    y += b;
	if ( y > a ) {
		y += func4(a, b, y-1);
		return y;
	} else if ( a > y ) {
		y += func4(a, y+1, c);
		return y;
	} else {
		return y;
	}
}

int gamer(int x) {
	int ecx = 0;
	int edx = x & 0xf;
	ecx += 7 + edx*4;
}

int func7(long *a, long b, int eax) {
	if ( a == 0 ) {
		return 0xffffffff;
	}
	int edx = *a;
	if ( edx > b ) {
		a += 8;
		return func7( a, b, eax )*2;
	} else {
		eax = 0;
		if ( edx != b ) {
			eax = func7( a + 16, b, eax );
			return eax*2 + 1;
		} else {
			return eax;
		}
	}
}

long address(int a) {
	long rdx = 0x5555555571c0;
	return rdx * 2 + 4 * a;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "dumbass\n");
        return 1;
    }

    int a = atoi(argv[1]);
	a = 0x0000000000000007;

	long result = 0;
	//for ( a; a < 0xffffffff; a += 0x0000000f ) {
		result = address(a);
		printf("Result: %x\n", result);
	//}

    return 0;
}
