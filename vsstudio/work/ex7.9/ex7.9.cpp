#include <iostream>
using namespace std;

class Car {
private:
	int number;
	static int count;
public:
	Car(int n);
	void ShowCar();
	static int GetCount();
};

int Car::count = 0;

Car::Car(int n) {
	number = n;
	count++;
}

void Car::ShowCar() {
	cout << "번호 : " << number << endl;
}

int Car::GetCount() {
	return count;
}

void main() {
	Car c1(1234);
	c1.ShowCar();
	cout << "등록대수 : " << Car::GetCount() << endl;

	Car c2(2345);
	c2.ShowCar();
	cout << "등록대수 : " << Car::GetCount() << endl;

	Car c3(3456);
	c3.ShowCar();
	cout << "등록대수 : " << Car::GetCount() << endl;
}