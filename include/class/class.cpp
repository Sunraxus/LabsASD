#ifndef INCLUDE_CLASS_CLASS_H_
#define INCLUDE_CLASS_CLASS_H_

#pragma once
#include <Vector.cpp>
#include <stdexcept>
#include <cmath>
#include <complex>
#include <iostream>
#include <iosfwd>
using namespace std;

namespace polynomials {

	bool operator>=(const std::complex<double>& a, const std::complex<double>& b) {
		return std::abs(a) >= std::abs(b);
	}

	bool operator<(const std::complex<double>& a, const std::complex<double>& b) {
		return std::abs(a) < std::abs(b);
	}

	bool operator>=(const std::complex<float>& a, const std::complex<float>& b) {
		return std::abs(a) >= std::abs(b);
	}

	bool operator<(const std::complex<float>& a, const std::complex<float>& b) {
		return std::abs(a) < std::abs(b);
	}

	template<typename T>
	class Polynomial {
		Vector<T> _coeff;
	public:
		Polynomial();
		Polynomial(int max_level);
		Polynomial(const Vector<T>& other);
		const Vector<T>& get_coeffs() const;
		T& operator[](int level);
		T operator[](int level) const;
		Polynomial<T> set(T coeff, int level);
		Polynomial<T> operator+=(const Polynomial<T>& other);
		Polynomial<T> operator+(const Polynomial<T>& other)const;
		Polynomial<T> operator-=(const Polynomial<T>& other);
		Polynomial<T> operator-(const Polynomial<T>& other)const;
		Polynomial<T> operator*(const T& scalar) const; 
		template <typename T1>
		friend Polynomial<T> operator*(const T& scalar, const Polynomial<T>& other);
		T compute(T argument);
		Polynomial<T> shrink_to_fit();
		Polynomial<T>& expand(int level);
		bool operator==(Polynomial<T>& other) const;
		bool operator!=(Polynomial<T>& other) const;
		Polynomial<T>& operator=(Polynomial<T> other);
		~Polynomial() = default;
		const T coeff_at(int index) const;
		friend std::ostream& operator<<(std::ostream& out, const Polynomial<T>& poly) {
			int new_size = poly._coeff.get_size() - 1;

			for (int i = new_size; i >= 0; --i) {
				T coeff = poly.coeff_at(i);
				if (i < new_size) {
					if (coeff >= T(0)) {
						out << " + ";
					}
					if (coeff < T(0)) {
						out << " ";
					}
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
	const Vector<T>& Polynomial<T>::get_coeffs() const {
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
		if (level < 0) {
			throw runtime_error("Invalid level"); }
		if (level > _coeff.get_size()) {
			expand(level);
			_coeff[level-1] = coeff;
			return *this;
		}
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
		int max_size = max(_coeff.get_size(), other._coeff.get_size());
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
		int max_size = max(_coeff.get_size(), other._coeff.get_size());
		Polynomial<T> result(max_size);

		for (int i = 0; i < max_size; ++i) {
			T coeff1 = (i < _coeff.get_size()) ? _coeff[i] : 0;
			T coeff2 = (i < other._coeff.get_size()) ? other._coeff[i] : 0;

			result._coeff[i] = coeff1 - coeff2;
		}

		return result;
	}
	
	template<typename T>
	Polynomial<T> Polynomial<T>::operator*(const T& scalar) const {
		Polynomial<T> result = *this; 
		for (int i = 0; i < result._coeff.get_size(); ++i) {
			result._coeff[i] = result._coeff[i] * scalar;
		}
		return result;
	}
	
	template<typename T>
	Polynomial<T> operator*(const T& scalar, const Polynomial<T>& other) {
		Polynomial<T> result = other;
		for (int i = 0; i < result._coeff.get_size(); ++i) {
			result._coeff[i] = scalar * result._coeff[i];
		}
		return result;
	}

	template<typename T>
	T Polynomial<T>::compute(T arg) {
		T result = 0;
		T current_pos = 1;
		for (int i = 0; i < _coeff.get_size(); ++i) {
			result += _coeff[i] * current_pos;
			current_pos *= arg;
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


	template<typename T>
	Polynomial<T> integral_compute(Polynomial<T>& other) {
		Polynomial<T> integral(other);
		int new_size = integral.get_coeffs().get_size();
		integral.expand(new_size + 1);
		for (int i = 0; i < new_size; ++i) {
			T coeff = other.coeff_at(i);
			T new_coeff = coeff / (i + 1);
			integral[i + 1] = new_coeff;
		}
		integral[0] = 0;
		return integral;
	}
}
#endif