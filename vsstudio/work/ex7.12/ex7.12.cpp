#include <iostream>
#include <string>
using namespace std;
class CPU
{
private:
	string cpuname;
	float speed;
public:
	CPU(string cn, float sp) : cpuname(cn), speed(sp) { }
	void show() const {
		cout << "processor name: " << cpuname << ", speed :" \
			<< speed << " GHz" << endl;
	}
};class Computer
{
private:
	CPU c_cpu; // ¸â¹ö °´Ã¼
	int m_size;
public:
	Computer(CPU cpu1, int size) : c_cpu(cpu1), m_size(size) { }
	~Computer() { };
	void show() {
		c_cpu.show();
		cout << "memory : " << m_size << " GB" << endl;
	}
};void main()
{
	CPU mycpu("Intel i7", 2.2f);
	Computer mycom(mycpu, 16);
	mycom.show();
}