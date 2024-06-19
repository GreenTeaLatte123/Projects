#include <iostream>
#include <string>
using namespace std;

void main()
{
	int num;
	char ch = 'A';
	cout << "정수를 입력하시오: ";
	cin >> num;
	cout << "num:" << num << ".ch: " << ch << endl;

	string str;
	str = "Hello";
	str = str + "!";
	cout << str << endl;
}