#include <iostream>
using namespace std;

struct Student
{
	int id;
	char name[10];
	float score;
};

void main() {

	Student stu1;

	cout << "�й��� �Է��Ͻÿ�: \t";
	cin >> stu1.id;
	cout << "�̸��� �Է��Ͻÿ�: \t";
	cin >> stu1.name;
	cout << "������ �Է��Ͻÿ�: \t";
	cin >> stu1.score;
	cout << endl;

	cout << "�й�: " << stu1.id << endl;
	cout << "�̸�: " << stu1.name << endl;
	cout << "����: " << stu1.score << endl;
}