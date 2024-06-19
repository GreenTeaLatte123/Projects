#include <iostream>
using namespace std;
class Vehicle
{
protected:
	int number;
public:
	Vehicle(int n) :number(n) { };
	void Show() const;
};
void Vehicle::Show() const
{
	cout << "Vehicle::Show() ==> ";
	cout << "번호: " << number << endl;
}

class Truck :public Vehicle
{
private:
	int cargo;
public:
	Truck(int n, int c) :Vehicle(n) { cargo = c; };
	void Show() const;
};
void Truck::Show() const
{
	cout << "Truck::Show() ==> ";
	cout << "번호: " << number << ", 화물 적재량: " << cargo << endl;
}

void main()
{
	Vehicle v(1234);
	cout << "v ==> ";
	v.Show();
	Truck t(3456, 40);
	cout << "t ==> ";
	t.Show();
	cout << "t ==> ";
	t.Vehicle::Show();
	cout << endl;
}
