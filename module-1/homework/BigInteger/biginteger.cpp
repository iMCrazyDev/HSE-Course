//
// Created by Dev1l on 11.09.2020.
//

#include "BigInteger.h"

const int base = 1e9;
#define PI 3.14159265358979323846
typedef std::complex<double> cmplex;
void BigInteger::Sum(BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger copy = BigInteger(rhs);
	//TODO: сделать хд
	if (lhs.sign == 1 && rhs.sign == 1)
	{
		lhs = -lhs;
		copy = -copy;
		Sum(lhs, copy);
		RevSign(lhs);
	}
	else if (lhs.sign == 1)
	{
		Sum(copy, lhs);
		lhs = copy;
		RevSign(lhs);
	}

	if (rhs.sign == 1)
	{
		if (lhs < -rhs)
		{
			lhs = -lhs;
			copy = -copy;
			Sum(copy, lhs);
			lhs = copy;
			RevSign(lhs);

		}
		else
		{
			int rems = 0;
			int lastindnul = -1;

			for (int i = 0; i < lhs.vec.size(); i++)
			{
				if (lhs.vec.size() == i) lhs.vec.push_back(0);
				lhs.vec[i] += rems;

				if (copy.vec.size() > i)
					lhs.vec[i] -= copy.vec[i];

				if (lhs.vec[i] == 0 && lastindnul == -1)
				{
					lastindnul = i;
				}
				else
				{
					lastindnul = -1;
					if (lhs.vec[i] < 0)
					{
						lhs.vec[i] += base; rems -= 1;
					}
				}
				//rems = lhs.vec[i] / base;
				//lhs.vec[i] %= base;
			}
			if (lastindnul != -1) lhs.vec.erase(lhs.vec.begin() + lastindnul, lhs.vec.end());
			if (lhs.vec.size() == 0) lhs.vec.push_back(0);
		}
	}
	else
	{
		int mx = lhs.vec.size();
		if (copy.vec.size() > mx) mx = copy.vec.size();
		int rems = 0;
		for (int i = 0; (i < mx) || rems != 0; i++)
		{
			if (i == mx)
			{
				lhs.vec.push_back(rems);
				break;
			}
			if (lhs.vec.size() == i) lhs.vec.push_back(0);
			lhs.vec[i] += rems;

			if (copy.vec.size() > i)
				lhs.vec[i] += copy.vec[i];

			rems = lhs.vec[i] / base;
			lhs.vec[i] %= base;
		}
	}
	//return *lhs;
}

void BigInteger::RevSign(BigInteger& bi)
{
	if (bi.sign == 0) bi.sign = 1;
	else bi.sign = 0;
}

bool BigInteger::GreaterThan(const BigInteger& rhs) const
{
	bool result = false;

	if (sign == 0 && rhs.sign == 1) result = true;
	else if (sign == 1 && rhs.sign == 0) result = false;
	else
	{
		if (vec.size() > rhs.vec.size()) result = true;
		else if (vec.size() < rhs.vec.size()) result = false;
		else
		{
			for (int i = vec.size() - 1; i >= 0; i--)
			{
				if (vec[i] > rhs.vec[i]) result = true;
				else if (vec[i] < rhs.vec[i]) result = false;
				else continue;
				break;
			}
		}
	}
	if (rhs.sign == 1 && sign == 1) result = !result;
	return result;
}

void BigInteger::fft(std::vector<cmplex>& a, bool invert) {
	int n = (int)a.size();
	if (n == 1)  return;

	std::vector<cmplex> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i < n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);
	cmplex w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i < n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

int BigInteger::Max(const int& a, const int& b)
{
	return a > b ? a : b;
}

void BigInteger::Multiply(BigInteger& lhs, const BigInteger& rhs)
{
	std::vector<cmplex> fa(lhs.vec.begin(), lhs.vec.end()), fb(rhs.vec.begin(), rhs.vec.end());
	size_t n = 1;
	while (n < Max((int)lhs.vec.size(), (int)rhs.vec.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft(fb, false);
	for (size_t i = 0; i < n; ++i)
		fa[i] *= fb[i];
	fft(fa, true);

	std::vector<unsigned int> res(n);
	for (size_t i = 0; i < n; ++i)
		res[i] = int(fa[i].real() + 0.5);
	int bb3 = res.size() - 1;
	while (bb3 > 0 && res[bb3] == 0) bb3--;
	res.erase(res.begin() + bb3 + 1, res.end());
	lhs.vec = res;

	if (lhs.sign != rhs.sign) RevSign(lhs);
}


BigInteger BigInteger::Divide(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger b1 = BigInteger(lhs);
	BigInteger b2 = BigInteger(rhs);
	BigInteger b3 = BigInteger(1);
	int a = 0;
	if (lhs.sign == 1) { a++; RevSign(b1); }
	if (rhs.sign == 1) { a++; RevSign(b2); }
	BigInteger res = Divide(b1, b2, b3, b1);

	if (a % 2 == 0) return res;
	else {
		return -res;
	}
}

BigInteger BigInteger::Divide(const BigInteger& lhs, int rhs)
{
	int i3 = rhs;
	BigInteger res;
	res.vec.clear();
	res.sign = lhs.sign;
	if (i3 < 0) {
		RevSign(res); i3 = -i3;
	}
	int cry = 0;
	for (int i = lhs.vec.size() - 1; i >= 0; i--)
	{
		int val = lhs.vec[i];
		long long curval = val + cry * 1LL * base;
		res.vec.insert(res.vec.begin(), curval / i3);
		cry = curval % i3;
	}

	return res;
}
BigInteger BigInteger::Divide(BigInteger& lhs, BigInteger& rhs, BigInteger& start, BigInteger& end)
{
	BigInteger current = Divide((end + start), 2);
	BigInteger plus_one = current + BigInteger(1);
	BigInteger minus_one = current - BigInteger(1);

	BigInteger val = current * rhs;
	BigInteger next = plus_one * rhs;
	BigInteger prev = minus_one * rhs;

	/*BigInteger val = Multiply(current, rhs);
	BigInteger next = Multiply(plus_one, rhs);
	BigInteger prev = Multiply(minus_one, rhs);*/

	if (val == lhs || (val < lhs && next > lhs))
	{
		return current;
	}
	else if (val > lhs && prev < lhs)
	{
		return minus_one;
	}
	else if (val < lhs)
	{
		return Divide(lhs, rhs, plus_one, end);
	}
	else if (val > lhs)
	{
		return Divide(lhs, rhs, start, minus_one);
	}
	return lhs;
}

void BigInteger::Reset()
{
	sign = 0;
	vec.clear();
	vec.push_back(0);
}

void BigInteger::Set(BigInteger& rhs)
{
	this->vec = rhs.vec;
	this->sign = rhs.sign;
}

std::string BigInteger::toString()
{
	std::string result;

	for (auto z : BigInteger::vec)
	{
		result = std::to_string(z) + result;
	}

	if (sign == 1) result = "-" + result;
	return result;
}

BigInteger::BigInteger()
{
	sign = 0;
	vec.push_back(0);
}

BigInteger::BigInteger(int sig, std::vector<unsigned int> ve)
{
	BigInteger::vec = ve;
	BigInteger::sign = sig;
}

void BigInteger::InitFromString(const char* str)
{
	std::string st = std::string(str);
	sign = 0;
	if (str[0] == '-') { sign = -1; st = st.substr(1); }
	if (str[0] == '+') { st = st.substr(1); }

	while (st.size() > 0)
	{
		int am = 8;
		if (st.size() < am) am = st.size();
		auto cur = st.substr(st.size() - am, am);
		if (st.size() > am)
			st = st.substr(0, st.size() - am);
		else st = "";
		vec.push_back(atoi(cur.c_str()));
	}

}

BigInteger::operator bool()
{
	return vec.size() > 0 && vec[0] != 0;
}

BigInteger::operator std::string()
{
	return BigInteger::toString();
}

BigInteger::BigInteger(int inp)
{
	sign = 0;
	if (inp < 0) { sign = 1; inp *= -1; }
	vec.push_back(inp);
}

BigInteger::BigInteger(const char* str)
{
	InitFromString(str);
}

BigInteger::BigInteger(std::string& str)
{
	InitFromString(str.c_str());
}

BigInteger::BigInteger(const BigInteger& bi) : vec(bi.vec), sign(bi.sign) {}

BigInteger& BigInteger::operator=(const BigInteger& rhs)
{
	if (this != &rhs)
	{
		vec = rhs.vec;
		sign = rhs.sign;
	}
	return *this;
}

BigInteger& BigInteger::operator=(int& inp)
{
	vec.clear();
	sign = 0;
	if (inp < 0) { sign = 1; inp *= -1; }
	vec.push_back(inp);
	return *this;
}



BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger bb3 = lhs;
	bb3 *= rhs;
	return bb3;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs)
{
	Multiply(*this, rhs);
	return *this;
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger _bi = lhs;
	_bi += rhs;
	return _bi;
}


BigInteger& BigInteger::operator++() {
	Sum(*this, 1);
	return *this;
}

BigInteger BigInteger::operator--(int a)
{
	BigInteger prev = *this;
	Sum((*this), -1);
	return prev;
}

BigInteger BigInteger::operator++(int a)
{
	BigInteger prev = *this;
	Sum((*this), 1);
	return prev;
}

BigInteger& BigInteger::operator--()
{
	Sum((*this), -1);
	return *this;
}


BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger bi = lhs;
	bi -= rhs;
	return bi;
}

BigInteger BigInteger::operator-() const
{
	BigInteger bi = BigInteger(*this);
	RevSign(bi);
	return bi;
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs)
{
	Sum((*this), rhs);
	return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs)
{
	Sum((*this), -rhs);
	return (*this);
}


BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger bb3 = lhs;
	bb3 %= rhs;
	return bb3;
}

BigInteger& BigInteger::operator%=(const BigInteger& rhs)
{
	BigInteger res = (*this) - BigInteger::Divide((*this), rhs) * rhs;
	Set(res);
	return *this;
}


BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger bb3 = lhs;
	bb3 /= rhs;
	return bb3;
}


BigInteger& BigInteger::operator/=(const BigInteger& rhs)
{
	BigInteger res = Divide(*this, rhs);
	Set(res);
	return *this;
}



bool BigInteger::Equals(const BigInteger& lhs) const
{
	return sign == lhs.sign && vec == lhs.vec;
}

std::ostream& operator<<(std::ostream& out, BigInteger& bi)
{
	out << bi.toString();
	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& bi)
{
	bi.Reset();
	std::string st;
	in >> st;
	int sign = 0;
	if (st[0] == '-') {
		st = st.substr(1); sign = -1;
	}
	if (st.size() >= 9)
	{
		BigInteger bi2 = BigInteger(st);
		bi.vec = bi2.vec;
		bi.sign = sign;
	}
	else
	{
		int inp = atoi(st.c_str());
		bi += inp;
		bi.sign = sign;
	}
	return in;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
	return lhs.Equals(rhs);
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
	return !lhs.Equals(rhs);
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs)
{
	return lhs.GreaterThan(rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs)
{
	return lhs.GreaterThan(rhs) || rhs.Equals(lhs);
}

bool operator<(const BigInteger& lhs, const  BigInteger& rhs)
{
	return rhs.GreaterThan(lhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs)
{
	return rhs.GreaterThan(lhs) || rhs.Equals(lhs);
}