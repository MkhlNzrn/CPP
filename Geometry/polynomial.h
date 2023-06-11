#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>


#define INC_2_POLYNOMIAL_H


class Polynomial {
public:
	int size;
	int minPow;
	int maxPow;
	int *coefficents;
public:
	Polynomial(int, int, int *);

	Polynomial(const Polynomial &other);

	Polynomial();

	Polynomial &plusOrMinus(bool isNegative, const Polynomial &poly_);

	Polynomial &removeZero();


	Polynomial &operator=(const Polynomial &poly_);

	friend bool operator==(const Polynomial &poly1_, const Polynomial &poly2_);

	friend bool operator!=(const Polynomial &poly1_, const Polynomial &poly2_);

	Polynomial &operator+=(const Polynomial &poly_);

	friend Polynomial operator*(const Polynomial &poly1_, const Polynomial &poly2_);

	friend Polynomial operator*(const int &coef, const Polynomial &poly2_);

	friend Polynomial operator*(const Polynomial &poly2_, const int &coef);

	Polynomial &operator*=(const Polynomial &poly_);

	friend Polynomial operator+(const Polynomial &poly1_, const Polynomial &poly2_);

	friend Polynomial operator-(const Polynomial &poly_);


	Polynomial &operator-=(const Polynomial &poly_);

	friend Polynomial operator-(const Polynomial &poly1_, const Polynomial &poly2_);

	friend Polynomial operator/(const Polynomial &poly_, int coef);

	Polynomial &operator/=(const int &coef);

	friend std::istream &operator>>(std::istream &in, Polynomial &poly_);

	friend std::ostream &operator<<(std::ostream &out, const Polynomial &poly_);

	int &operator[](int coef);

	int operator[](int) const;
};
