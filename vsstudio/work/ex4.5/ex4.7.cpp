#include <iostream>
using namespace std;

struct student {
	int id;
	char name[20];
};

int main() {
	student stu1 = { 1234, "Hong Gildong" };
	student stu2 = { 2345, "Lee Soonsin" };
	student* pstu;
	pstu = &stu2;

	cout << "std1.id : " << stu1.id << "stu1.name : " \
		<< stu1.name << endl;

	cout << "(*pstu).id : " << (*pstu).id << "(*pstu).name : " \
		<< (*pstu).name << endl;

	cout << "pstu->id : " << pstu->id << "pstu->id.name : " \
		<< pstu->name << endl;

	return 0;
}