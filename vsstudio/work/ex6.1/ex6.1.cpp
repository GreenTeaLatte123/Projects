#include <iostream>
using namespace std;

class Rectangle
{
private :
	int width;
	int height;

public :
	void GetRect(int w, int h);
	void ShowRect();
};

void Rectangle::GetRect(int w, int h) {
	width = w;
	height = h;
}

void Rectangle::ShowRect() {
	cout << "width = " << width << ", height = " << height << endl;
}

void main() {
	Rectangle r;
	//r.width = 5;
	//r.height = 4;
	r.GetRect(5, 4);
	r.ShowRect();
}