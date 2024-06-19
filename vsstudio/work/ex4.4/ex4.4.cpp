#include <iostream>
using namespace std;

void main() {
	int num1 = 10, num2 = 20;
	int* pnum = &num1;
	cout << "*pnum = " << *pnum << endl;

	pnum = &num2;
	cout << "*pnum = " << *pnum << endl;
}