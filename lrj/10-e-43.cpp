#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;

LL pow10[15];
LL gcd(LL a, LL b, LL& x, LL& y) {
	if (b == 0) {x = 1, y = 0; return a;}
	LL res = gcd(b, a % b, y, x);
	y -= a / b * x;
	return res;
}

void cal(LL a, LL b, LL n, LL limit, vector<PLL>& res) {
	res.clear();
	LL x, y, d = gcd(a, b, x, y), k = n / d;
	if (n % d) return;
	x *= k, y *= k, a /= d, b /= d;
	for (int i = 30; i >= 0; --i) {
		LL t = 1LL << i;
		if (y - t * a >= 0) y -= t * a, x += t * b;
		if (y + t * a <= 0) y += t * a, x -= t * b;
	}
	if (y < 0) y += a, x -= b;
	while (x >= 0 && y < limit) {
		res.push_back(make_pair(x, y));
		y += a, x -= b;
	}
}
int getlen(LL x) {
	int res = 0;
	while (x) res++, x /= 10;
	return res;
}
void solve() {
	LL n;
	vector<PLL> tmp;
	map<LL, LL> ans;
	scanf("%lld", &n);
	int len = getlen(n);
	for (int i = 0; i < len; ++i)
		for (int x = 0; x < 10; ++x) {
			cal(pow10[i + 1] + pow10[i], 2, n - x * pow10[i], pow10[i], tmp);
			for (auto p : tmp) {
				LL X = p.first * pow10[i + 1] + x * pow10[i] + p.second;
				LL Y = p.first * pow10[i] + p.second;
				if (X == Y) continue;
				ans[X] = Y;
			}
		}
	printf("%lld\n", ans.size());
	for (const auto& p : ans) printf("%lld + %0*lld = %lld\n", p.first, getlen(p.first) - 1, p.second, n);
}

int main() {
	pow10[0] = 1;
	for (int i = 1; i <= 10; ++i) pow10[i] = pow10[i - 1] * 10;
	int T; scanf("%d", &T);
	while (T--) {
		solve();
		if (T) puts("");
	}
	return 0;
}