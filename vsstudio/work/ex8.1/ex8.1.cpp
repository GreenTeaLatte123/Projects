#include <iostream>
using namespace std;

class Time {
protected:
	int hours;
	int minutes;
public:
	Time(int h, int m) :hours(h), minutes(m) {};
	void showTime() const
	{
		cout << hours << "½Ã°£" << minutes << "ºÐ" << endl;
	}
	Time operator+(const Time& t) const;
};

Time Time::operator+(const Time& t) const {
	Time tsum(0, 0);
	int m1, m2;

	m1 = hours * 60 + minutes;
	m2 = t.hours * 60 + t.minutes;
	tsum.hours = (m1 + m2) / 60;
	tsum.minutes = (m1 + m2) % 60;
	return tsum;
}

void main() {
	Time t1(2, 25), t2(3, 45), ts(0, 0);
	cout << "t1 => ";
	t1.showTime();
	cout << "t2 => ";
	t2.showTime();

	cout << "t1.operator+(t2) => ";
	ts = t1.operator+(t2); // ts = t1 + t2;
	ts.showTime();
	cout << "t1 + t2 => ";
	ts = t1 + t2;
	ts.showTime();
}