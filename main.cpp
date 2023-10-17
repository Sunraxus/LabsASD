#include<class.cpp>
#include<iostream>
#include<complex>
using namespace std;
using namespace polynomials;

int main() {
	Vector<std::complex<double>> vec1(2);
	vec1[0] = std::complex<double>(1.2, 12.2);
	vec1[1] = std::complex<double>(-3.4, 2.6);
	Polynomial<std::complex<double>> polynomial1(vec1);
	cout << polynomial1 << endl;
	Polynomial<std::complex<double>> polynomial2 = polynomial1 * 5;
	cout << polynomial2 << endl;
	/*Polynomial<int> pol1(7);

	pol1[0] = 1;
	pol1[1] = 0;
	pol1[2] = -3;

	cout << pol1 << endl;

	pol1.shrink_to_fit();

	cout << pol1 << endl;

	pol1.expand(5);

	cout << pol1 << endl;*/
}
