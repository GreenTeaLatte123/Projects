#include <iostream>
using namespace std;

class Car {
private:
	int number;
public:
	static int count;
	Car(int n);
	void ShowCar();
};

int Car::count = 0;

Car::Car(int n) {
	number = n;
	count++;
}

void Car::ShowCar() {
	cout << "��ȣ : " << number << endl;
}

void main() {
	Car c1(1234);
	c1.ShowCar();
	cout << "��ϴ�� : " << c1.count << endl;
	
	Car c2(2345);
	c2.ShowCar();
	cout << "��ϴ�� : " << c2.count << endl;

	Car c3(3456);
	c3.ShowCar();
	cout << "��ϴ�� : " << c3.count << endl;
}