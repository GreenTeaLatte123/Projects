#include <iostream>
using namespace std;

void swap(int*, int*);

void main() {
	int a = 20, b = 30;

	cout << "(swap ����) a = " << a << ", b = " << b << endl;
	swap(&a, &b);
	cout << "(swap ����) a = " << a << ", b = " << b << endl;
}

void swap(int *x, int *y){
	int z;
	z = *x;
	*x = *y;
	*y = z;
}