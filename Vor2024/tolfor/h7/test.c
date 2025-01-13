#include <stdio.h>
int rec(int n, int m)
{
if (n >= m) { // comparator fyrir línur 1 og 2
m+=m; // Lína 6
n-=2; // Lína 7
// Hérna sameina ég línur 8, 9 og 11, kallað er á fallið í línu 8,
// svo er einum bætt við skilagildi fallsins í línu 9 og skilað í línu 11.
return rec(n,m) + 1;
}
return 0; // Ef hoppið gerist ekki, er jafnt línum 3 og 4
}
int main() {
	int x = rec(1, 2);
	printf("%d\n", x);
	return 0;
}
