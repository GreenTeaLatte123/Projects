#include <iostream>
using namespace std;

void main() {
	bool a = true, b = true, c = false;
	cout << "a: " << a << ",b: " << b << ",c: " << c << endl;
	bool d = 5, e = -3, f = 0;
	cout << "d: " << d << ",e: " << e << ",f: " << f << endl;

	cout << "bool형의 크기: " << sizeof(a) << "바이트" << endl;
}