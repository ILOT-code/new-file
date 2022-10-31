#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 10;
int n, m, mod, a[maxn];
LL d[maxn << 2], add[maxn << 2], mul[maxn << 2];

void build(int p, int s, int t) {
	mul[p] = 1; add[p] = 0;
	if (s == t) { d[p] = a[s] % mod; return; }
	int m = (s + t) >> 1;
	build(2 * p, s, m); build(2 * p + 1, m + 1, t);
	d[p] = (d[2 * p] + d[2 * p + 1]) % mod;
}

void pushdown(int s, int t, int p) {
	if (add[p] == 0 && mul[p] == 1) return;
	if (s == t) return;
	int m = (s + t) >> 1;
	add[2 * p] = (add[2 * p] * mul[p] + add[p]) % mod, add[2 * p + 1] = (add[2 * p + 1] * mul[p] + add[p]) % mod;
	mul[2 * p] = (mul[2 * p] * mul[p]) % mod, mul[2 * p + 1] = (mul[2 * p + 1] * mul[p] % mod);
	d[2 * p] = (d[2 * p] * mul[p] + (m - s + 1) * add[p]) % mod, d[2 * p + 1] = (d[2 * p + 1] * mul[p] + (t - m) * add[p]) % mod;
	add[p] = 0, mul[p] = 1;
}
void update1(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] = (d[p] + 1ll * (t - s + 1) * c) % mod; add[p] = (add[p] + c) % mod;
		return;
	}
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	if (m >= l) update1(l, r, c, s, m, 2 * p);
	if (m < r) update1(l, r, c, m + 1, t, 2 * p + 1);
	d[p] = (d[2 * p] + d[2 * p + 1]) % mod;
}

void update2(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] = (d[p] * c) % mod; mul[p] = (mul[p] * c) % mod; add[p] = (add[p] * c) % mod;
		return;
	}
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	if (m >= l) update2(l, r, c, s, m, 2 * p);
	if (m < r) update2(l, r, c, m + 1, t, 2 * p + 1);
	d[p] = (d[2 * p] + d[2 * p + 1]) % mod;
}

LL getsum(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) { return d[p] % mod;}
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	LL ret = 0;
	if (m >= l) ret += getsum(l, r, s, m, 2 * p);
	if (m < r) ret += getsum(l, r, m + 1, t, 2 * p + 1);
	return ret % mod;
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	build(1, 1, n);
	for (int i = 1, f, x, y, k; i <= m; ++i) {
		scanf("%d%d%d", &f, &x, &y);
		if (f == 1) {
			scanf("%d", &k);
			update2(x, y, k, 1, n, 1);
		}
		else if (f == 2) {
			scanf("%d", &k);
			update1(x, y, k, 1, n, 1);
		}
		else printf("%lld\n", getsum(x, y, 1, n, 1));
	}
	return 0;
}