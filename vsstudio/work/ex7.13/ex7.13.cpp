#include <iostream>
#include <string>
using namespace std;

class Point
{
private:
	int px; // private ���
	int py; // private ���
public:
	Point(int x = 0, int y = 0) :px(x), py(y) { }
	void showPoint() const {
		cout << "���� ��ġ: x = " << px << ", y = " << py << endl;
	}
	friend class Circle; // Circle Ŭ�������� px, py�� ����ϱ� ����
};

class Circle
{
private:
	Point center; // ��� ��ü
	int radius;
public:
	Circle(Point cen, int rad = 0) :center(cen), radius(rad) { }
	~Circle() { };
	void showCircle() {
		cout << "�߽���: (x = " << center.px << ", y = " << center.py << ")";
		// Point Ŭ������ private ��� ���� px�� py�� ����ϱ� ���Ͽ�
		// Point Ŭ�������� Circle Ŭ������ friend Ŭ������ �����Ͽ���.
		cout << " ������: " << radius << endl;
	}
};

void main()
{
	Point cen(5, 7);
	cen.showPoint();
	Circle cir1(cen, 10);
	cir1.showCircle();
}
