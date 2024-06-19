#include <iostream>
using namespace std;

void main() {
	int *id;
	id = new int;
	cout << "번호를 입력하세요: ";
	cin >> *id;

	char* name = new char[20];
	cout << "이름을 입력하세요: ";
	cin >> name;

	cout << "id : " << *id << ". name: " << name << endl;
	
	delete id;
	delete[] name;
}