#include <iostream>
using namespace std;

class Vehicle {
private:
	int number;
	int year;
public:
	Vehicle(int num, int yr);
	~Vehicle();
	void ShowVehicle() const;
};

Vehicle::Vehicle(int n = 0, int y = 0):number(n), year(y){
}

Vehicle::~Vehicle(){
}

void Vehicle::ShowVehicle() const {
	cout << "Number : " << number << ", Year : " << year << endl;
}

void main() {
	Vehicle v1;
	Vehicle v2(1234);
	Vehicle v3(1234, 2012);

	v1.ShowVehicle();
	v2.ShowVehicle();
	v3.ShowVehicle();
}