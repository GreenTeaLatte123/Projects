#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
private:
	int number;
public:
	Vehicle(int n) :number(n) {
		cout << "Vehicle 생성자" << endl;
	};
	~Vehicle() {
		cout << "Vehicle 소멸자, " << number << endl;
	};
	void ShowNumber() const;
};

void Vehicle::ShowNumber() const {
	cout << "번호: " << number << endl;
}

class Truck :public Vehicle {
private:
	int cargo;
public:
	Truck(int n, int c) :Vehicle(n) {
		cargo = c;
		cout << "Truck 생성자" << endl;
	}
	~Truck() {
		cout << "Vehicle 소멸자, " << cargo << endl;
	}
	void ShowCargo() const;
};

void Truck::ShowCargo() const {
	cout << "화물: " << cargo << endl;
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