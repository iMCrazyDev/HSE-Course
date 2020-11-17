//
// Created by Dev1l on 11.09.2020.
//
#include <vector>
#include <iostream>
#include <complex> //for fft

#define uint unsigned int

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

class BigInteger {
private:
	std::vector<uint> vec;


	int sign;
	void Reset();
	void Set(BigInteger& bi);
	BigInteger(int sign, std::vector<uint> vec);
	void InitFromString(const char*);

	static void RevSign(BigInteger& bi);
	static BigInteger Divide(BigInteger& bi, BigInteger& bi2, BigInteger& start, BigInteger& end);
	static BigInteger Divide(const BigInteger&, int);
	static void fft(std::vector<std::complex<double>>& a, bool invert);
	static int Max(const int& a, const int& b);
	bool GreaterThan(const BigInteger& other) const;
public:
	static void Sum(BigInteger& bi, const BigInteger& bi2);
	static BigInteger Divide(const BigInteger& bi, const BigInteger& bi2);
	static void Multiply(BigInteger& bi, const BigInteger& bi2);
	BigInteger();
	BigInteger(int);
	BigInteger(const char*);
	BigInteger(std::string&);
	BigInteger(const BigInteger&);

	operator std::string();
	explicit operator bool();
	std::string toString();

	friend std::ostream& operator<< (std::ostream& out, BigInteger& bi);
	friend std::istream& operator>> (std::istream& in, BigInteger& bi);

	BigInteger& operator=  (const BigInteger& right);
	BigInteger& operator=  (int& right);

	friend bool operator== (const BigInteger& left, const BigInteger& right);
	friend bool operator!= (const BigInteger& left, const BigInteger& right);
	friend bool operator>  (const BigInteger& left, const BigInteger& right);
	friend bool operator>= (const BigInteger& left, const BigInteger& right);
	friend bool operator<  (const BigInteger& left, const BigInteger& right);
	friend bool operator<= (const BigInteger& left, const BigInteger& right);

	BigInteger operator++(int a);
	BigInteger operator--(int a);

	BigInteger operator- () const;
	friend BigInteger operator+ (const BigInteger& _add, const BigInteger& add);
	friend BigInteger operator- (const BigInteger& _add, const BigInteger& add);
	friend BigInteger operator* (const BigInteger& _add, const BigInteger& add);
	friend BigInteger operator% (const BigInteger& _add, const BigInteger& bi);
	friend BigInteger operator/ (const BigInteger& _add, const BigInteger& bi);

	BigInteger& operator*= (const BigInteger& add);
	BigInteger& operator++();
	BigInteger& operator--();
	BigInteger& operator+=(const BigInteger& add);
	BigInteger& operator-=(const BigInteger& add);
	BigInteger& operator/=(const BigInteger& bi);
	BigInteger& operator%=(const BigInteger& bi);

	bool Equals(const BigInteger& bi) const;
};






#endif //BIGINTEGER_BIGINTEGER_H
