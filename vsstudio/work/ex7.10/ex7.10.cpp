#include <iostream>
#include <cstring>
using namespace std;

class Car
{
private:
	int number;
	char* owner;
public:
	Car(int n, char* m); // ������, ����Լ�
	void showCar() const; // ����Լ�
	friend void printCar(Car car[], int n); // ������ �Լ�
};Car::Car(int n, char* m)
{
	number = n;
	owner = new char[strlen(m) + 1];
	strcpy_s(owner, strlen(m) + 1, m);
}
void Car::showCar() const
{
	cout << "��ȣ: " << number << ", ������: " << owner << endl;
}

void printCar(Car car[], int n) // ��ü �迭�� ���޹޴´�
{
	int i;
	for (i = 0; i < n; i++)
		cout << "car[" << i << "] ==> " << car[i].number \
		<< ", " << car[i].owner << endl;
}
void main()
{
	Car car[3] = { Car(1234, (char*)"Kim"), Car(2345, (char*)"Hong"), Car(3456, (char*)"Lee") };
	car[0].showCar(); // ����Լ��̹Ƿ� ��ü�� �Բ� ���
	printCar(car, 3); // ����Լ��� �ƴϹǷ� ��ü�� �̸��� �Բ� ����� �� ����.
	// �Ϲ��Լ�ó�� ȣ���Ͽ��� �Ѵ�. ��ü �迭�� �̸��� ����
	cout << endl;
}