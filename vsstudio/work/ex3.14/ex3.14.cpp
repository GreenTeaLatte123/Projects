#include <iostream>
using namespace std;

void main() {
	int i, sum;

	i = 0, sum = 0;
	while (i < 100) {
		i++;
		sum += i;
	}
	cout << "1���� 100���� ������ ���� " << sum << endl;
}