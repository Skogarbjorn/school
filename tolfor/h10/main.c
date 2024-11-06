void fun();
extern int b;
short int c = 5;

int main() {
	b = 3;
	fun();
	c = 6;
	
	return 0;
}
