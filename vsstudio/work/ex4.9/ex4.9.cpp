#include <iostream>
using namespace std;

void main() {
	int *id;
	id = new int;
	cout << "��ȣ�� �Է��ϼ���: ";
	cin >> *id;

	char* name = new char[20];
	cout << "�̸��� �Է��ϼ���: ";
	cin >> name;

	cout << "id : " << *id << ". name: " << name << endl;
	
	delete id;
	delete[] name;
}