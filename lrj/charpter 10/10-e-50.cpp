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


int n, m, cnt, sub[255], comp[255], vis[255], ans[255];
Bigint K, p[255][255];

void init() {
	for (int i = 0; i <= 250; ++i)
		for (int j = i; j >= 0; --j) {
			if (i == j) p[i][j] = 1;
			else p[i][j] = p[i][j + 1] * (j + 1);
		}
}

void dfs(int cur, int cur_sub, Bigint k) {
	if (cur == n) {
		cout << ans[0];
		for (int i = 1; i < n; ++i) cout << ' ' << ans[i];
		cout << endl; return;
	}
	Bigint tmp;
	for (int i = 0, used = 0;;) {
		if (vis[comp[i]]) {i++; continue;}
		if (i >= cnt) {
			ans[cur] = sub[cur_sub];
			dfs(cur + 1, cur_sub + 1, k);
			return;
		}
		if (cur_sub < m && sub[cur_sub] < comp[i] && !used) {
			used = 1; tmp = p[n - cur - 1][m - cur_sub - 1];
			if (K < k + tmp) {
				ans[cur] = sub[cur_sub];
				dfs(cur + 1, cur_sub + 1, k);
				return;
			} else k += tmp;
		}
		else {
			tmp = p[n - cur - 1][m - cur_sub];
			if (K < k + tmp) {
				vis[comp[i]] = 1; ans[cur] = comp[i];
				dfs(cur + 1, cur_sub, k);
				return;
			} else {k += tmp; i++;}
		}
	}
}

int main() {
	init();
	while (cin >> n >> m >> K) {
		K = K - 1;
		memset(vis, 0, sizeof(vis));
		cnt = 0;
		for (int i = 0; i < m; ++i) {
			cin >> sub[i];
			vis[sub[i]] = 1;
		}
		for (int i = 1; i <= n; ++i)
			if (!vis[i]) comp[cnt++] = i;
		dfs(0, 0, 0);
	}
	return 0;
}