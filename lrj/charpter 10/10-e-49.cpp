#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
typedef map<int, int> IMAP;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void factor(int a, IMAP& ans) {
	ans.clear();
	for (int i = 2; i * i <= a; ++i)
		while (a % i == 0) a /= i, ans[i]++;
	if (a > 1) ans[a] = 1;
}

LL powerTpwers(int n) {
	if (n == 1) return 1;
	IMAP f; factor(n, f);
	LL ans = 0;
	int e = 1;
	for (auto p : f) e = max(e, p.second);
	for (int i = 1; i <= e; ++i) {
		bool valid = true;
		for (auto p : f) if (p.second % i != 0) { valid = false; break; }
		if (valid) ans += powerTpwers(i);
	}
	return ans;
}

int main() {
	int a, b, c;
	IMAP fa, fb, fg;
	while (~scanf("%d^%d^%d", &a, &b, &c)) {
		factor(a, fa), factor(b, fb);
		int g = 0;
		for (auto p : fa) g = gcd(g, p.second);
		factor(g, fg);
		for (auto p : fb) fg[p.first] += p.second * c;

		int maxc = 1;
		for (auto p : fg) maxc = max(maxc, p.second);
		LL sum = 0;
		for (int w = 2; w <= maxc; ++w) {
			LL tmp = 1;
			for (auto p : fg) tmp *= (p.second / w + 1);
			sum += (tmp - 1) * powerTpwers(w);
		}
		printf("%lld\n", sum);
	}
	return 0;
}