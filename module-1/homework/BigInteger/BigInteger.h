//
// Created by Dev1l on 11.09.2020.
//
#include <vector>
#include <iostream>
#include <complex> 

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

class BigInteger {

public:
	BigInteger();
	BigInteger(int);
	BigInteger(const char*);
	BigInteger(std::string&);
	BigInteger(const BigInteger&);

	static void Sum(BigInteger& bi, const BigInteger& bi2);
	static BigInteger Divide(const BigInteger& lhs, const BigInteger& rhs);
	static void Multiply(BigInteger& bi, const BigInteger& bi2);

	operator std::string();
	explicit operator bool();
	std::string toString();

	friend std::ostream& operator<<(std::ostream& out, BigInteger& bi);
	friend std::istream& operator>>(std::istream& in, BigInteger& bi);

	BigInteger& operator=(const BigInteger& right);
	BigInteger& operator=(int& right);

	friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);

	BigInteger operator++(int a);
	BigInteger operator--(int a);

	BigInteger operator-() const;
	friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs);

	BigInteger& operator*=(const BigInteger& rhs);
	BigInteger& operator++();
	BigInteger& operator--();
	BigInteger& operator+=(const BigInteger& rhs);
	BigInteger& operator-=(const BigInteger& rhs);
	BigInteger& operator/=(const BigInteger& rhs);
	BigInteger& operator%=(const BigInteger& rhs);

	bool Equals(const BigInteger& bi) const;

private:
	BigInteger(int sign, std::vector<unsigned int> vec);
	std::vector<unsigned int> vec;
	bool sign;
	void Reset();
	void Set(BigInteger& bi);
	void InitFromString(const char*);
	static void RevSign(BigInteger& bi);
	static BigInteger Divide(BigInteger& lhs, BigInteger& rhs, BigInteger& start, BigInteger& end);
	static BigInteger Divide(const BigInteger& lhs, int rhs);
	static void fft(std::vector<std::complex<double>>& a, bool invert);
	static int Max(const int& a, const int& b);
	bool GreaterThan(const BigInteger& other) const;
};

#endif //BIGINTEGER_BIGINTEGER_H
