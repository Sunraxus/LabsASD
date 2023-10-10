#include<class.cpp>
#include<iostream>
using namespace std;
using namespace polynomials;

int main() {
	Vector<int> vec1(7);
	Vector<int> vec2(10);

	for (int i = 0; i < vec1.get_size(); ++i) {
		vec1[i] = i;
	}
	for (int i = 0; i < vec2.get_size(); ++i) {
		vec2[i] = i - 8;
	}


	Polynomial<int> polynomial1(vec1);
	Polynomial<int> polynomial2(vec2);

	cout << polynomial1 << endl;
	cout << polynomial2 << endl;
}
