#include <iostream>
#include <cstring>
using namespace std;

class Car
{
private:
	int number;
	char* owner;
public:
	Car(int n, char* m); // 생성자, 멤버함수
	void showCar() const; // 멤버함수
	friend void printCar(Car car[], int n); // 프렌드 함수
};Car::Car(int n, char* m)
{
	number = n;
	owner = new char[strlen(m) + 1];
	strcpy_s(owner, strlen(m) + 1, m);
}
void Car::showCar() const
{
	cout << "번호: " << number << ", 소유주: " << owner << endl;
}

void printCar(Car car[], int n) // 객체 배열로 전달받는다
{
	int i;
	for (i = 0; i < n; i++)
		cout << "car[" << i << "] ==> " << car[i].number \
		<< ", " << car[i].owner << endl;
}
void main()
{
	Car car[3] = { Car(1234, (char*)"Kim"), Car(2345, (char*)"Hong"), Car(3456, (char*)"Lee") };
	car[0].showCar(); // 멤버함수이므로 객체와 함께 사용
	printCar(car, 3); // 멤버함수가 아니므로 객체의 이름과 함께 사용할 수 없다.
	// 일반함수처럼 호출하여야 한다. 객체 배열의 이름을 전달
	cout << endl;
}