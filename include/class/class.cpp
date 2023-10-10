#ifndef INCLUDE_CLASS_CLASS_H_
#define INCLUDE_CLASS_CLASS_H_

#include <Vector.cpp>
#include <stdexcept>
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

namespace polynomials {

	template<typename T>
	class Polynomial {
		Vector<T> _coeff;
	public:
		Polynomial();
		Polynomial(int max_level);
		Polynomial(const Vector<T>& other);
		Vector<T>& get_coeffs();
		T& operator[](int level);
		T operator[](int level) const;
		Polynomial<T> set(T coeff, int level);
		Polynomial<T> operator+=(const Polynomial<T>& other);
		Polynomial<T> operator+(const Polynomial<T>& other)const;
		Polynomial<T> operator-=(const Polynomial<T>& other);
		Polynomial<T> operator-(const Polynomial<T>& other)const;
		Polynomial<T> operator*(const T scalar) const;
		T compute(T argument);
		Polynomial<T> shrink_to_fit();
		Polynomial<T>& expand(int level);
		bool operator==(Polynomial<T>& other) const;
		bool operator!=(Polynomial<T>& other) const;
		Polynomial<T>& operator=(Polynomial<T> other);
		~Polynomial() = default;
		const T coeff_at(int index) const;
		friend std::ostream& operator<<(std::ostream& out, const Polynomial<T>& poly) { //всё еще выводит + c -...
			int new_size = poly._coeff.get_size() - 1;

			for (int i = new_size; i >= 0; --i) {
				T coeff = poly.coeff_at(i);
				if (i < new_size) {
					out << " + ";
				}
				if (i > 0) {
					out << coeff << "x^" << i;
				}
				else {
					out << coeff;
				}
			}
			return out;
		}
	};

	template<typename T>
	Polynomial<T>::Polynomial() {
		this->_coeff = Vector<T>();
	}

	template<typename T>
	Polynomial<T>::Polynomial(int max_level) {
		this->_coeff = Vector<T>(max_level);
	}

	template<typename T>
	Polynomial<T>::Polynomial(const Vector<T>& other) {
		_coeff = other;
	}

	template<typename T>
	Vector<T>& Polynomial<T>::get_coeffs() {
		return _coeff;
	}

	template<typename T>
	T& Polynomial<T>::operator[](int level) {
		if (level < 0 || level >= _coeff.get_size()) {
			throw runtime_error("Invalid level");
		}
		return _coeff[level];
	}

	template<typename T>
	T Polynomial<T>::operator[](int level) const {
		if (level < 0 || level >= _coeff.get_size()) {
			throw runtime_error("Invalid level");
		}
		return _coeff[level];
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::set(T coeff, int level) {
		if (level < 0 || level > _coeff.get_size()) { throw runtime_error("Invalid level"); }
		if (coeff == 0) { return *this; } // корректное поведение?
		_coeff[level] = coeff;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator+=(const Polynomial<T>& other) {
		_coeff += other._coeff;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& other) const {
		int max_size = std::max(_coeff.get_size(), other._coeff.get_size());
		Polynomial<T> result(max_size);

		for (int i = 0; i < max_size; ++i) {
			T coeff1 = (i < _coeff.get_size()) ? _coeff[i] : 0;
			T coeff2 = (i < other._coeff.get_size()) ? other._coeff[i] : 0;

			result._coeff[i] = coeff1 + coeff2;
		}

		return result;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator-=(const Polynomial<T>& other) {
		_coeff -= other._coeff;
		return *this;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& other) const {
		int max_size = std::max(_coeff.get_size(), other._coeff.get_size());
		Polynomial<T> result(max_size);

		for (int i = 0; i < max_size; ++i) {
			T coeff1 = (i < _coeff.get_size()) ? _coeff[i] : 0;
			T coeff2 = (i < other._coeff.get_size()) ? other._coeff[i] : 0;

			result._coeff[i] = coeff1 - coeff2;
		}

		return result;
	}
	
	template<typename T>
	Polynomial<T> Polynomial<T>::operator*(const T scalar) const {
		Polynomial<T> result = *this; 
		for (int i = 0; i < result._coeff.get_size(); ++i) {
			result._coeff[i] *= scalar;
		}
		return result;
	}
	
	template<typename T>
	T Polynomial<T>::compute(T arg) {
		T result = 0;
		for (int i = 0; i < _coeff.get_size(); ++i) {
			result += static_cast<T>(_coeff[i]) * static_cast<T>(pow(arg, i)); // можно ли использовать приведение типов?
		}
		return result;
	}

	template<typename T>
	Polynomial<T> Polynomial<T>::shrink_to_fit() {
		int new_size = _coeff.get_size();

		while (new_size > 0 && _coeff[new_size - 1] == T(0)) {
			new_size--;
		}

		Polynomial<T> result(new_size);

		for (int i = 0; i < new_size; i++) {
			result._coeff[i] = _coeff[i];
		}
		_coeff = result._coeff;
		return *this;
	}

	template<typename T>
	Polynomial<T>& Polynomial<T>::expand(int level) {
		Polynomial<T> temp(level);
		for (int i = 0; i < _coeff.get_size(); ++i) {
			temp[i] = _coeff[i];
		}
		_coeff = temp.get_coeffs();
		return *this;
	}

	template<typename T>
	bool Polynomial<T>::operator==(Polynomial<T>& other) const {
		return (this->_coeff == other._coeff);
	}

	template<typename T>
	bool Polynomial<T>::operator!=(Polynomial<T>& other) const {
		return (this->_coeff != other._coeff);
	}

	template<typename T>
	const T Polynomial<T>::coeff_at(int index) const {
		return _coeff[index];
	}

	template<typename T>
	Polynomial<T>& Polynomial<T>::operator=(Polynomial<T> other) {
		std::swap(_coeff, other._coeff);
		return *this;
	}

	/*template <std::complex<float>>
	std::ostream& operator<<(std::ostream& out, const Polynomial<std::complex<float>>& poly) {
		int new_size = poly._coeff.get_size() - 1;

		for (int i = new_size; i >= 0; --i) {
			std::complex<float> coeff = poly.coeff_at(i);
			if (coeff != std::complex<float>(0.0f, 0.0f)) {
				if (i < new_size) {
					out << " + ";
				}
				if (i > 0) {
					out << "(" << coeff.real();
					if (coeff.imag() >= 0) {
						out << "+";
					}
					out << coeff.imag() << "i)";
					out << "x^" << i;
				}
				else {
					out << "(" << coeff.real();
					if (coeff.imag() >= 0) {
						out << "+";
					}
					out << coeff.imag() << "i)";
				}
			}
		}
		return out;
	}

	template <std::complex<double>>
	std::ostream& operator<<(std::ostream& out, const Polynomial<std::complex<double>>& poly) {
		int new_size = poly._coeff.get_size() - 1;

		for (int i = new_size; i >= 0; --i) {
			std::complex<double> coeff = poly.coeff_at(i);
			if (coeff != std::complex<double>(0.0, 0.0)) {
				if (i < new_size) {
					out << " + ";
				}
				if (i > 0) {
					out << "(" << coeff.real();
					if (coeff.imag() >= 0) {
						out << "+";
					}
					out << coeff.imag() << "i)";
					out << "x^" << i;
				}
				else {
					out << "(" << coeff.real();
					if (coeff.imag() >= 0) {
						out << "+";
					}
					out << coeff.imag() << "i)";
				}
			}
		}
		return out;
	}*/ //вывод работает но некорректно 

}
#endif