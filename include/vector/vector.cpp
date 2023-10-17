#ifndef INCLUDE_VECTOR_VECTOR_H_
#define INCLUDE_VECTOR_VECTOR_H_
#pragma once
#include <stdexcept>
#include <iostream>

const float epsilon = 0.0001f;

namespace polynomials {

	template <typename T>
	class Vector {
		int _size;
		T* _ptr;
	public:
		Vector();
		Vector(int size);
		Vector(const Vector<T>& other);
		int get_size()const;
		T* get_ptr();
		Vector<T>& operator=(const Vector<T>& other);
		void Swap(Vector<T>& other);
		bool operator==(const Vector<T>& other) const;
		bool operator!=(const Vector<T>& other) const;
		Vector& operator+=(const Vector<T>& other);
		Vector& operator-=(const Vector<T>& other);
		~Vector();
		T& operator[](int num);
		T operator[](int num) const;
	};

	template <typename T>
	Vector<T>::Vector() {
		this->_ptr = nullptr;
		this->_size = 0;
	}

	template <typename T>
	Vector<T>::Vector(int size) {
		this->_size = size;
		this->_ptr = new T[size]{ 0 };
	}

	template <typename T>
	Vector<T>::~Vector() {
		if (this->_ptr != nullptr) {
			delete[] this->_ptr;
		}
	}

	template <typename T>
	int Vector<T>::get_size() const {
		return _size;
	}

	template<typename T>
	T* Vector<T>::get_ptr() {
		return _ptr;
	}

	template <typename T>
	bool Vector<T>::operator==(const Vector<T>& other) const {
		if (this->_size == other._size) {
			for (int i = 0; i < this->_size; i++) {
				if ((*this)[i] != other[i]) return false;
			}
			return true;
		}
		return false;
	}

	bool Vector<float>::operator==(const Vector<float>& other) const {
		if (this->_size == other._size) {
			for (int i = 0; i < this->_size; i++) {
				if (fabs((*this)[i] - other[i]) <= epsilon) return false;
			}
			return true;
		}
		return false;
	}


	template <typename T>
	bool Vector<T>::operator!=(const Vector<T>& other) const {
		return !((*this) == other);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
		int new_size = (_size > other._size) ? _size : other._size;
		Vector<T> result(new_size);

		for (int i = 0; i < new_size; ++i) {
			if (i < _size) {
				result._ptr[i] += _ptr[i];
			}
			if (i < other._size) {
				result._ptr[i] += other._ptr[i];
			}
		}

		Swap(result);
		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
		int new_size = (_size > other._size) ? _size : other._size;
		Vector<T> result(new_size);

		for (int i = 0; i < new_size; ++i) {
			if (i < _size) {
				result._ptr[i] += _ptr[i];
			}
			if (i < other._size) {
				result._ptr[i] -= other._ptr[i];
			}
		}

		Swap(result);
		return *this;
	}


	template <typename T>
	T& Vector<T>::operator[](int num) {
		if (num < 0 || num >= this->_size) {
			throw std::out_of_range("Index out of range");
		}
		return this->_ptr[num];
	}

	template <typename T>
	T Vector<T>::operator[](int num) const {
		if (num < 0 || num >= this->_size) {
			throw std::out_of_range("Index out of range");
		}
		return this->_ptr[num];
	}


	template <typename T>
	void Vector<T>::Swap(Vector<T>& other) {
		std::swap(this->_ptr, other._ptr);
		std::swap(this->_size, other._size);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
		Vector<T> other_copy(other);
		this->Swap(other_copy);
		return *this;
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& other) {
		this->_size = other._size;
		this->_ptr = new T[_size];
		for (int i = 0; i < _size; i++) {
			this->_ptr[i] = other[i];
		}
	}
}
#endif 