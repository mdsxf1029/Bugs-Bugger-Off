/* 2354264 ��11 л���� */
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	const double pi = 3.14159;
	double r, h;
	cout << "������뾶�͸߶�" << endl;
	cin >> r >> h;
	double c, s, S, v, V;
	c = 2 * pi * r;
	s = pi * r * r;
	S = 4 * pi * r * r;
	v = pi * r * r * r * 4 / 3;
	V = pi * r * r * h;
	cout << setiosflags(ios::fixed);
	cout << setprecision(2) << "Բ�ܳ�     : " << c << endl;
	cout << setprecision(2) << "Բ���     : " << s << endl;
	cout << setprecision(2) << "Բ������ : " << S << endl;
	cout << setprecision(2) << "Բ�����   : " << v << endl;
	cout << setprecision(2) << "Բ�����   : " << V << endl;
	return 0;
}