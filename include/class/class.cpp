#ifndef INCLUDE_Polynomial_Polynomial_H_
#define INCLUDE_Polynomial_Polynomial_H_

#include <Vector.cpp>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

namespace polynomials {

	template<typename T>
	class Polynomial {
		Vector<T> _coeffs;
	public:

		Polynomial();
		Polynomial(int max_level);
		Polynomial(const Vector<T>& other);
		Vector<T>& get_coeffs();
		Polynomial<T> set(T coeff, int level);
		T compute(T argument);
		Polynomial<T> operator+=(const Polynomial<T>& other);
		Polynomial<T> operator+(const Polynomial<T>& other)const;
		Polynomial<T> operator-=(const Polynomial<T>& other);
		Polynomial<T> operator-(const Polynomial<T>& other)const;
		Polynomial<T> operator*(const T num) const;
		Polynomial<T> operator[](int level) const;
		bool operator==(Polynomial<T>& other) const;
		bool operator!=(Polynomial<T>& other) const;
		Polynomial<T> shrink_to_fit();
		Polynomial<T> expand(int level);
		~Polynomial() = default;
	};

	template<typename T>
	Polynomial<T>::Polynomial() {
		this->_coeffs = Vector<T>();
	}

	template<typename T>
	Polynomial<T>::Polynomial(int max_level) {
		this->_coeffs = Vector<T>(max_level);
	}

	template<typename T>
	Polynomial<T>::Polynomial(const Vector<T>& other) {
		_coeffs = other;
	}

	template<typename T>
	Vector<T>& Polynomial<T>::get_coeffs()
	{
		return _coeffs;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::set(T coeff, int level) {
		if (level < 0 || level > _coeffs.get_size()) { throw runtime_error("Invalid level"); }
		if (coeff == 0) { return *this; }
		_coeffs[level] = coeff;
		return *this;
	}

	template<typename T>
	T Polynomial<T>::compute(T arg) {
		T sum;
		for (int i = 0; i < _coeffs.get_size(); ++i) {
			sum += _coeffs[i] * pow(arg, i);
		}
		return sum;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator+=(const Polynomial<T>& other) {
		_coeffs += other._coeffs;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& other) const {
		int maxSize = std::max(_coeffs.get_size(), other._coeffs.get_size());
		Polynomial<T> result(maxSize);

		for (int i = 0; i < maxSize; ++i) {
			T coeff1 = (i < _coeffs.get_size()) ? _coeffs[i] : 0;
			T coeff2 = (i < other._coeffs.get_size()) ? other._coeffs[i] : 0;

			result._coeffs[i] = coeff1 + coeff2;
		}

		return result;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator-=(const Polynomial<T>& other) {
		_coeffs -= other._coeffs;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& other) const {
		int maxSize = std::max(_coeffs.get_size(), other._coeffs.get_size());
		Polynomial<T> result(maxSize);

		for (int i = 0; i < maxSize; ++i) {
			T coeff1 = (i < _coeffs.get_size()) ? _coeffs[i] : 0;
			T coeff2 = (i < other._coeffs.get_size()) ? other._coeffs[i] : 0;

			result._coeffs[i] = coeff1 - coeff2;
		}

		return result;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator*(T skal) const {
		int maxSize = std::max(_coeffs.get_size(), _coeffs.get_size());
		Polynomial<T> result(maxSize);

		for (int i = 0; i < maxSize; ++i) {
			T coeff1 = (i < _coeffs.get_size()) ? _coeffs[i] : 0;

			result._coeffs[i] = coeff1 * skal;
		}

		return result;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator[](int level) const {
		if (level < 0 || level >= _coeffs.get_size()) {
			throw runtime_error("Invalid level");
		}
		return _coeffs[level];
	}

	template<typename T>
	bool Polynomial<T>::operator==(Polynomial<T>& other) const {
		return (this->_coeffs == other._coeffs);
	}

	template<typename T>
	bool Polynomial<T>::operator!=(Polynomial<T>& other) const {
		return (this->_coeffs != other._coeffs);
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::shrink_to_fit() {
		int newSize = _coeffs.get_size();

		while (newSize > 0 && _coeffs[newSize - 1] == T(0)) {
			newSize--;
		}

		Polynomial<T> result(newSize);

		for (int i = 0; i < newSize; i++) {
			result._coeffs[i] = _coeffs[i];
		}
		_coeffs = result._coeffs;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::expand(int level) {
		Polynomial<T> temp(level);
		for (int i = 0; i <= temp._coeffs.get_size(); ++i) {
			temp[i] = _coeffs[i];
		}
		_coeffs = temp;
		return *this;
	}
}
#endif