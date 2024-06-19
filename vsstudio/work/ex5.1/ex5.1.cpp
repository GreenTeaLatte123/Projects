#include <iostream>
using namespace std;

int add(int, int);
void multiply(int, int);

void main(void) {
	int a = 15, b = 10, sum;
	sum = add(a, b);
	cout << a << " + " << b << " = " << sum << endl;
	multiply(a, b);

	return;
}

int add(int x, int y) {
	int sum;
	sum = x + y;

	return sum;
}

void multiply(int x, int y) {
	cout << x << " * " << y << " = " << x * y << endl;
}