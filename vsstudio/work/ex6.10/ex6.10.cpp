#include <iostream>
using namespace std;
class Vehicle
{
private:
	int number;
	int year;
public:
	Vehicle(int number = 0, int year = 0);
	~Vehicle();
	void ShowVehicle() const;
};

Vehicle::Vehicle(int number, int year)
{
	this->number = number;
	// this->number�� number�� ������� number�̰�,
	// ���� number�� ��ü ������ �� �ִ� ���̴�.
	this->year = year;
	// this->year�� year�� ������� year�̰�,
	// ���� year�� ��ü ������ �� �ִ� ���̴�.
}
Vehicle::~Vehicle()
{
}
void Vehicle::ShowVehicle() const {
	cout << "Number : " << this->number << ", Year : " << this->year << endl;
}

void main()
{
	Vehicle v1(1234, 2012);
	cout << "v1.ShowVehicle()" << "==> ";
	v1.ShowVehicle();
	cout << endl;
	Vehicle* pv;
	pv = &v1;
	cout << "pv->ShowVehicle()" << "==> ";
	pv->ShowVehicle();
}
