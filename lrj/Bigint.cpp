#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;

struct Bigint {
	vector<LL> s;
	static const LL BASE = 1e4;
	static const int WIDTH = 4;
	void Normal() {
		while (s.size() && !s.back()) s.pop_back();
		if (s.empty()) s.push_back(0);
	}
	Bigint(LL x = 0) {*this = x;}
	Bigint(const string& str) {*this = str;}
	Bigint& operator=(LL x) {
		s.clear();
		for (; x; x /= BASE) s.push_back(x % BASE);
		Normal(); return *this;
	}
	Bigint& operator=(const string& str) {
		s.clear(); LL n = str.size();
		for (LL i = n - 1; i >= 0;) {
			LL j = max(0LL, i - WIDTH + 1), x;
			sscanf(str.substr(j, i - j + 1).c_str(), "%lld", &x);
			s.push_back(x);
			i = j - 1;
		}
		Normal(); return *this;
	}
	Bigint& operator+=(const Bigint&);
	Bigint& operator-=(const Bigint&);
	Bigint& operator*=(const Bigint&);
	Bigint& operator/=(const Bigint&);
};
istream& operator>>(istream& in, Bigint& x) {
	string s;
	if (!(in >> s)) return in;
	x = s; return in;
}
ostream& operator<<(ostream& out, const Bigint& x) {
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; --i) {
		char buf[20];
		sprintf(buf, "%0*lld", x.WIDTH, x.s[i]);
		out << buf;
	}
	return out;
}
bool operator<(const Bigint& a, const Bigint& b) {
	if (a.s.size() != b.s.size()) return a.s.size() < b.s.size();
	for (LL i = a.s.size() - 1; i >= 0; --i)
		if (a.s[i] != b.s[i]) return a.s[i] < b.s[i];
	return false;
}
bool operator==(const Bigint& a, const Bigint& b) {return a.s == b.s;}
Bigint operator+(const Bigint& a, const Bigint& b) {
	LL na = a.s.size(), nb = b.s.size(), n = max(na, nb);
	Bigint c; c.s.resize(n + 1, 0);
	for (LL i = 0; i < n; ++i) {
		if (i < na) c.s[i] += a.s[i];
		if (i < nb) c.s[i] += b.s[i];
		c.s[i + 1] += c.s[i] / c.BASE;
		c.s[i] %= c.BASE;
	}
	c.Normal(); return c;
}
Bigint operator-(const Bigint& a, const Bigint& b) {
	LL na = a.s.size(), nb = b.s.size(), n = na;
	Bigint c; c.s.resize(n + 1, 0);
	for (LL i = 0; i < n; ++i) {
		c.s[i] += a.s[i] + c.BASE;
		if (i < nb) c.s[i] -= b.s[i];
		c.s[i + 1] += c.s[i] / c.BASE - 1;
		c.s[i] %= c.BASE;
	}
	c.Normal(); return c;
}
Bigint operator*(const Bigint& a, const Bigint& b) {
	LL na = a.s.size(), nb = b.s.size(), n = na + nb;
	Bigint c; c.s.resize(n + 1, 0);
	for (LL i = 0; i < na; ++i)
		for (LL j = 0; j < nb; ++j)
			c.s[i + j] += a.s[i] * b.s[j];
	for (LL i = 0; i < n; ++i) {
		c.s[i + 1] += c.s[i] / c.BASE;
		c.s[i] %= c.BASE;
	}
	c.Normal(); return c;
}
Bigint operator/(const Bigint& a, const Bigint& b) {
	if (b == 0) return 0;
	LL na = a.s.size();
	Bigint c, d; c.s.resize(na, 0);
	for (LL i = na - 1; i >= 0; --i) {
		d.s.insert(d.s.begin(), a.s[i]); d.Normal();
		LL L = 0, R = a.BASE - 1;
		while (L != R) {
			LL M = (L + R + 1) >> 1;
			Bigint p = b * M;
			if (p == d) {L = M; break;}
			else if (p < d) L = M;
			else R = M - 1;
		}
		c.s[i] = L; d -= b * L;
	}
	c.Normal(); return c;
}
Bigint& Bigint::operator+=(const Bigint& b) {return *this = *this + b;}
Bigint& Bigint::operator-=(const Bigint& b) {return *this = *this - b;}
Bigint& Bigint::operator*=(const Bigint& b) {return *this = *this * b;}
Bigint& Bigint::operator/=(const Bigint& b) {return *this = *this / b;}
bool operator>(const Bigint& a, const Bigint& b) {return b < a;}
bool operator>=(const Bigint& a, const Bigint& b) {return !(a < b);}
bool operator<=(const Bigint& a, const Bigint& b) {return !(b < a);}
bool operator!=(const Bigint& a, const Bigint& b) {return !(a == b);}

int main() {
	LL a = 10223;
	string s = "120";
	Bigint t1 = a, t2 = s;
	cout << t1 << endl;
	cout << t2 << endl;
	cout << t1 + t2 << endl;
	cout << t1 - t2 << endl;
	cout << t1*t2 << endl;
	cout << t1 / t2 << endl;
	return 0;
}