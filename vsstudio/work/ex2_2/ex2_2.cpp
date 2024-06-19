#include <iostream>
using namespace std;

void main() {
	char str1[6]{ 'k','o','r','e','a','\0' };
	char str2[6]{ "korea" };
	char str3[5]{ 'k','o','r','e','a' };
	//char str4[5]{ "korea" };

	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;
	cout << "str3: " << str3 << endl;
	
	cout << "str3: ";
	for (int i = 0; i < 5; i++)
		cout << str3[i];
	cout << endl;
}