#include <iostream>
using namespace std;

class Vehicle {
private:
	int number;
	int year;
public:
	Vehicle();
	Vehicle(int num, int yr);
	~Vehicle();
	void ShowVehicle() const;
};

Vehicle::Vehicle() {
	cout << "Vehicle ������" << endl;
	number = 0, year = 0;
}

Vehicle::Vehicle(int num, int yr) {
	cout << "Vehicle ������(number, year)" << endl;
	number = num;
	year = yr;
}

Vehicle::~Vehicle() {
	cout << number << "�� �Ҹ���" << endl;
}

void Vehicle::ShowVehicle() const {
	cout << "Number : " << number << ". Year : " << year << endl;
}

void main() {
	Vehicle v1;
	Vehicle v2(1234, 2012);

	v1.ShowVehicle();
	v2.ShowVehicle();
}