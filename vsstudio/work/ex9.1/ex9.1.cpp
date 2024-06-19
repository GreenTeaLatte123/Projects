#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
private:
	int number;
public:
	Vehicle(int n) :number(n) {
		cout << "Vehicle ������" << endl;
	};
	~Vehicle() {
		cout << "Vehicle �Ҹ���, " << number << endl;
	};
	void ShowNumber() const;
};

void Vehicle::ShowNumber() const {
	cout << "��ȣ: " << number << endl;
}

class Truck :public Vehicle {
private:
	int cargo;
public:
	Truck(int n, int c) :Vehicle(n) {
		cargo = c;
		cout << "Truck ������" << endl;
	}
	~Truck() {
		cout << "Vehicle �Ҹ���, " << cargo << endl;
	}
	void ShowCargo() const;
};

void Truck::ShowCargo() const {
	cout << "ȭ��: " << cargo << endl;
}

void main() {
	Vehicle v(1234);
	v.ShowNumber();
	cout << endl;

	Truck t(7890, 5);
	t.ShowNumber();
	t.ShowCargo();
	cout << endl;
}