#pragma once
#include<class.cpp>
#include<iostream>
#include<complex>
using namespace std;
using namespace polynomials;

int main() {
	/*Vector<std::complex<double>> vec1(2);
	vec1[0] = std::complex<double>(1.2, 12.2);
	vec1[1] = std::complex<double>(-3.4, 2.6);
	Polynomial<std::complex<double>> pol1(vec1);
	cout << pol1 << endl;
	Polynomial<std::complex<double>> pol2 = pol1;
	pol2 = integral_compute(pol1);
	cout << pol2 << endl;*/

	Polynomial<float> pol1(4);

	pol1[0] = 1;
	pol1[1] = 0;
	pol1[2] = -3;
	pol1[3] = 7;

	cout << pol1 << endl;

	Polynomial<float> pol2(4);

	pol2 = pol1 * 5;
	
	cout << pol2 << endl;
	
}
