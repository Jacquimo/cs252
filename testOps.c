#include <stdio.h>
#define null NULL

class testOps {
	int val;

public:
	testOps(int v) { val = v; }

	int operator+(testOps obj) {
		return val + obj.val;
	}
};

int main() {
	int a,b;

	printf("Enter two numbers:\n");
	scanf("%d %d", &a, &b);

	testOps f(a);
	testOps s(b);

	printf("%d\n", f + s);
	return 0;
}

