#include <iostream>
using namespace std;

void main() {
	int score;

	cout << "������ �Է��ϼ���(0~100): ";
	cin >> score;
	
	if (score >= 60)
		cout << "�հ��Դϴ�." << endl;
	else
		cout << "���հ��Դϴ�." << endl;
}