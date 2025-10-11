#include "HPD.hpp"
#include <ctime>
using namespace std;
HPD HPDsqrt(const HPD &hpd) {
	HPD a(1, 1), b = hpd;
	HPD two(2, 1);
	for(int i = 0; i < 100; ++i) {
		a += b;
		a = a / two;
		b = hpd / a;
		if(a == b) return a;
	}
	return a;
}
#include <cstdio>
int main() {
	time_t __t = clock();
	HPD::set_defprec(10000);
	HPD a(1, 1);
	HPD b = HPDsqrt(HPD(1, 2));
	HPD t(1, 4), p(1, 1);
	for(int i = 0; i < 100; ++i) {
		HPD a_n = (a + b) / HPD(2, 1);
		HPD b_n = HPDsqrt(a * b);
		HPD _t = a - a_n;
		HPD t_n = t - p * _t * _t;
		if(a == a_n && b == b_n && t == t_n) break;
		a = a_n;
		b = b_n;
		t = t_n;
		p = p * HPD(2, 1);
		cout << "i = " << i << endl;
		time_t t_ = clock();
		cout <<"time: "<< t_ - __t <<"ms"<< endl;
	}
	HPD ___t = a + b, four(4, 1);
	HPD pi = ___t * ___t / (t * four);
	cout << pi << endl;
	freopen("pi.out", "w", stdout);
	cout << pi << endl;
	time_t t__ = clock(), dt = t__ - __t;
	cout << dt << "ms" << endl;
	fclose(stdout);
	return 0;
}
