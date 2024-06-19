#include <iostream>
using namespace std;

int add(const int &, const int &);

void main() {
	int a = 20, b = 30, sum;

	sum = add(a, b);
	cout << "a + b = " << sum << endl;
}

int add(const int &x, const int &y) {
	int s;
	
	s = x + y;
	return s;
}