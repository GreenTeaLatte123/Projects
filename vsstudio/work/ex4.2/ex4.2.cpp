#include <iostream>
using namespace std;

void main() {
	int a[3] = { 10, 20, 30 };
	int i;

	for (i = 0; i < 3; i++)
		cout << i << " ��° ������ �ּ�: " << (a + i) << endl;
	cout << endl;
	
	for (i = 0; i < 3; i++)
		cout << i << " ��° ������ �ּ�: " << &a[i] << endl;
	cout << endl;

	for (i = 0; i < 3; i++)
		cout << i << " ��° ������ ��: " << a[i] << endl;
	cout << endl;

	for (i = 0; i < 3; i++)
		cout << i << " ��° ������ ��: " << *(a+i) << endl;
	cout << endl;

}