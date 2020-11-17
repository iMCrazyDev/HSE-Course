
//
// Created by Dev1l on 11.09.2020.
//

#include "BigInteger.h"

const int base = 1e9;
#define PI 3.14159265358979323846
typedef std::complex<double> cmplex;
void BigInteger::Sum(BigInteger& bi, const BigInteger& bi2)
{
	BigInteger copy = BigInteger(bi2);
	//TODO: сделать хд
	if (bi.sign == -1 && bi2.sign == -1)
	{
		bi = -bi;
		copy = -copy;
		Sum(bi, copy);
		RevSign(bi);
	}
	else if (bi.sign == -1)
	{
		Sum(copy, bi);
		bi = copy;
		RevSign(bi);
	}

	if (bi2.sign == -1)
	{
		if (bi < -bi2)
		{
			bi = -bi;
			copy = -copy;
			Sum(copy, bi);
			bi = copy;
			RevSign(bi);

		}
		else
		{
			int rems = 0;
			int lastindnul = -1;

			for (int i = 0; i < bi.vec.size(); i++)
			{
				if (bi.vec.size() == i) bi.vec.push_back(0);
				bi.vec[i] += rems;

				if (copy.vec.size() > i)
					bi.vec[i] -= copy.vec[i];

				if (bi.vec[i] == 0 && lastindnul == -1)
				{
					lastindnul = i;
				}
				else
				{
					lastindnul = -1;
					if (bi.vec[i] < 0)
					{
						bi.vec[i] += base; rems -= 1;
					}
				}
				//rems = bi.vec[i] / base;
				//bi.vec[i] %= base;
			}
			if (lastindnul != -1) bi.vec.erase(bi.vec.begin() + lastindnul, bi.vec.end());
			if (bi.vec.size() == 0) bi.vec.push_back(0);
		}
	}
	else
	{
		int mx = bi.vec.size();
		if (copy.vec.size() > mx) mx = copy.vec.size();
		int rems = 0;
		for (int i = 0; (i < mx) || rems != 0; i++)
		{
			if (i == mx)
			{
				bi.vec.push_back(rems);
				break;
			}
			if (bi.vec.size() == i) bi.vec.push_back(0);
			bi.vec[i] += rems;

			if (copy.vec.size() > i)
				bi.vec[i] += copy.vec[i];

			rems = bi.vec[i] / base;
			bi.vec[i] %= base;
		}
	}
	//return *bi;
}

void BigInteger::RevSign(BigInteger& bi)
{
	if (bi.sign == 0) bi.sign--;
	else bi.sign++;
}

bool BigInteger::GreaterThan(const BigInteger& other) const
{
	bool result = false;

	if (sign == 0 && other.sign == -1) result = true;
	else if (sign == -1 && other.sign == 0) result = false;
	else
	{
		if (vec.size() > other.vec.size()) result = true;
		else if (vec.size() < other.vec.size()) result = false;
		else
		{
			for (int i = vec.size() - 1; i >= 0; i--)
			{
				if (vec[i] > other.vec[i]) result = true;
				else if (vec[i] < other.vec[i]) result = false;
				else continue;
				break;
			}
		}
	}
	if (other.sign == -1 && sign == -1) result = !result;
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

void BigInteger::Multiply(BigInteger& bi, const BigInteger& bi2)
{
	std::vector<cmplex> fa(bi.vec.begin(), bi.vec.end()), fb(bi2.vec.begin(), bi2.vec.end());
	size_t n = 1;
	while (n < Max((int)bi.vec.size(), (int)bi2.vec.size()))  n <<= 1;
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
	bi.vec = res;

	if (bi.sign != bi2.sign) RevSign(bi);
}


BigInteger BigInteger::Divide(const BigInteger& bi, const BigInteger& bi2)
{
	BigInteger b1 = BigInteger(bi);
	BigInteger b2 = BigInteger(bi2);
	BigInteger b3 = BigInteger(1);
	int a = 0;
	if (bi.sign == -1) { a++; RevSign(b1); }
	if (bi2.sign == -1) { a++; RevSign(b2); }
	BigInteger res = Divide(b1, b2, b3, b1);

	if (a % 2 == 0) return res;
	else {
		return -res;
	}
}

BigInteger BigInteger::Divide(const BigInteger& bi, int i2)
{
	int i3 = i2;
	BigInteger res;
	res.vec.clear();
	res.sign = bi.sign;
	if (i3 < 0) {
		RevSign(res); i3 = -i3;
	}
	int cry = 0;
	for (int i = bi.vec.size() - 1; i >= 0; i--)
	{
		int val = bi.vec[i];
		long long curval = val + cry * 1LL * base;
		res.vec.insert(res.vec.begin(), curval / i3);
		cry = curval % i3;
	}

	return res;
}
BigInteger BigInteger::Divide(BigInteger& bi, BigInteger& bi2, BigInteger& start, BigInteger& end)
{
	BigInteger current = Divide((end + start), 2);
	BigInteger plus_one = current + BigInteger(1);
	BigInteger minus_one = current - BigInteger(1);

	BigInteger val = current * bi2;
	BigInteger next = plus_one * bi2;
	BigInteger prev = minus_one * bi2;

	/*BigInteger val = Multiply(current, bi2);
	BigInteger next = Multiply(plus_one, bi2);
	BigInteger prev = Multiply(minus_one, bi2);*/

	if (val == bi || (val < bi && next > bi))
	{
		return current;
	}
	else if (val > bi && prev < bi)
	{
		return minus_one;
	}
	else if (val < bi)
	{
		return Divide(bi, bi2, plus_one, end);
	}
	else if (val > bi)
	{
		return Divide(bi, bi2, start, minus_one);
	}
	return bi;
}

void BigInteger::Reset()
{
	sign = 0;
	vec.clear();
	vec.push_back(0);
}

void BigInteger::Set(BigInteger& bi)
{
	this->vec = bi.vec;
	this->sign = bi.sign;
}

std::string BigInteger::toString()
{
	std::string result;

	for (auto z : BigInteger::vec)
	{
		result = std::to_string(z) + result;
	}

	if (sign == -1) result = "-" + result;
	return result;
}

BigInteger::BigInteger()
{
	sign = 0;
	vec.push_back(0);
}

BigInteger::BigInteger(int sig, std::vector<uint> ve)
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
	if (inp < 0) { sign--; inp *= -1; }
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

BigInteger& BigInteger::operator=(const BigInteger& right)
{
	if (this != &right)
	{
		vec = right.vec;
		sign = right.sign;
	}
	return *this;
}

BigInteger& BigInteger::operator=(int& inp)
{
	vec.clear();
	sign = 0;
	if (inp < 0) { sign--; inp *= -1; }
	vec.push_back(inp);
	return *this;
}



BigInteger operator*(const BigInteger& me, const BigInteger& add)
{
	BigInteger bb3 = me;
	bb3 *= add;
	return bb3;
}

BigInteger& BigInteger::operator*=(const BigInteger& add)
{
	Multiply(*this, add);
	return *this;
}

BigInteger operator+(const BigInteger& bi, const BigInteger& bi2)
{
	BigInteger _bi = bi;
	_bi += bi2;
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


BigInteger operator-(const BigInteger& _add, const BigInteger& add)
{
	BigInteger bi = _add;
	bi -= add;
	return bi;
}

BigInteger BigInteger::operator-() const
{
	BigInteger bi = BigInteger(*this);
	RevSign(bi);
	return bi;
}

BigInteger& BigInteger::operator+=(const BigInteger& add)
{
	Sum((*this), add);
	return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& add)
{
	Sum((*this), -add);
	return (*this);
}


BigInteger operator%(const BigInteger& bi, const BigInteger& bi2)
{
	BigInteger bb3 = bi;
	bb3 %= bi2;
	return bb3;
}

BigInteger& BigInteger::operator%=(const BigInteger& bi)
{
	BigInteger res = (*this) - BigInteger::Divide((*this), bi) * bi;
	Set(res);
	return *this;
}


BigInteger operator/(const BigInteger& bi, const BigInteger& bi2)
{
	BigInteger bb3 = bi;
	bb3 /= bi2;
	return bb3;
}


BigInteger& BigInteger::operator/=(const BigInteger& bi)
{
	BigInteger res = Divide(*this, bi);
	Set(res);
	return *this;
}



bool BigInteger::Equals(const BigInteger& bi) const
{
	return sign == bi.sign && vec == bi.vec;
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

bool operator==(const BigInteger& left, const BigInteger& right)
{
	return left.Equals(right);
}

bool operator!=(const BigInteger& left, const BigInteger& right)
{
	return !left.Equals(right);
}

bool operator>(const BigInteger& left, const BigInteger& right)
{
	return left.GreaterThan(right);
}

bool operator>=(const BigInteger& left, const BigInteger& right)
{
	return left.GreaterThan(right) || right.Equals(left);
}

bool operator<(const BigInteger& left, const  BigInteger& right)
{
	return right.GreaterThan(left);
}

bool operator<=(const BigInteger& left, const BigInteger& right)
{
	return right.GreaterThan(left) || right.Equals(left);
}