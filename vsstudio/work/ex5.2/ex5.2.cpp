#include <iostream>
using namespace std;

#define abs1(x) (x<0) ? -(x) : (x)

inline int abs2(int y) {
	int m;
	m = y < 0 ? -y : y;
	return m;
}

int abs3(int z) {
	int m;
	m = z < 0 ? -z : z;
	return m;
}

int main(int argc, char* argv[]) {
	int a = -15, m1, m2, m3;

	m1 = abs1(a);
	cout << "(��ũ�� �Լ�) a = " << a << ". m1 = " << m1 << endl;

	m2 = abs2(a);
	cout << "(�ζ��� �Լ�) a = " << a << ". m2 = " << m2 << endl;

	m3 = abs3(a);
	cout << "(�Ϲ� �Լ�) a = " << a << ". m3 = " << m3 << endl;
}