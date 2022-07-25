#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

struct Fraction {
	LL a, b;
	Fraction(LL x = 0, LL y = 1): a(x), b(y) {this->reduce();}
	void reduce() {
		LL g = gcd(a, b);
		a = a / g;
		b = b / g;
		if (b < 0) {a = -a; b = -b;}
	}
	Fraction operator=(const Fraction&rhs) {
		a = rhs.a;
		b = rhs.b;
		return *this;
	}
	Fraction operator+(const Fraction& rhs) {
		Fraction ans;
		ans.b = lcm(b, rhs.b);
		ans.a = ans.b / b * a + ans.b / rhs.b * rhs.a;
		ans.reduce();
		return ans;
	}
	Fraction operator-(const Fraction& rhs) {
		Fraction ans;
		ans.b = lcm(b, rhs.b);
		ans.a = ans.b / b * a - ans.b / rhs.b * rhs.a;
		ans.reduce();
		return ans;
	}
	Fraction operator*(const Fraction& rhs) {
		Fraction ans;
		ans.a = a * rhs.a;
		ans.b = b * rhs.b;
		ans.reduce();
		return ans;
	}
	Fraction operator/(const Fraction& rhs) {
		Fraction ans;
		ans.a = a * rhs.b;
		ans.b = b * rhs.a;
		ans.reduce();
		return ans;
	}
	friend ostream& operator<<(ostream& out, const Fraction& rhs) {
		out << rhs.a << "/" << rhs.b;
		return out;
	}
	friend istream& operator>>(istream& in, Fraction& rhs) {
		in >> rhs.a >> rhs.b;
		rhs.reduce();
		return in;
	}
};

const int maxn = 20 + 5;
Fraction B[maxn], C[maxn][maxn], a[maxn];

void init() {
	for (int i = 0; i < maxn; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	B[0] = 1;
	for (int i = 1; i <= 20; ++i) {
		B[i] = 0;
		if (i > 2 && i & 1) continue;
		for (int j = 0; j < i; ++j) B[i] = B[i] - C[i + 1][j] * B[j];
		B[i] = B[i] / (i + 1);
	}
	B[1] = Fraction(1, 2);
}

int main() {
	int T, k;
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		LL L = 1;
		for (int i = 0; i <= k; ++i) {
			a[i] = C[k + 1][i] * B[i] / (k + 1);
			L = lcm(L, a[i].b);
		}
		if (L < 0) L = -L;
		printf("%lld ", L);
		for (int i = 0; i <= k; i++) printf("%lld ", L / a[i].b * a[i].a);
		printf("0\n");
		if (T) printf("\n");
	}
	return 0;
}
