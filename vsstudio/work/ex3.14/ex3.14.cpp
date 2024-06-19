#include <iostream>
using namespace std;

void main() {
	int i, sum;

	i = 0, sum = 0;
	while (i < 100) {
		i++;
		sum += i;
	}
	cout << "1부터 100까지 정수의 합은 " << sum << endl;
}