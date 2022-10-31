#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int maxn = 100000 + 10;
int n, m, a[maxn];
LL d[maxn << 2], b[maxn << 2];

void build(int p, int s, int t) {
	if (s == t) { d[p] = a[s]; return; }
	int m = (s + t) >> 1;
	build(2 * p, s, m); build(2 * p + 1, m + 1, t);
	d[p] = d[2 * p] + d[2 * p + 1];
}
void update(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] += 1ll * (t - s + 1) * c; b[p] += c;
		return;
	}
	int m = (s + t) >> 1;
	if (b[p] && s != t) {
		b[2 * p] += b[p]; b[2 * p + 1] += b[p];
		d[2 * p] += 1ll * (m - s + 1) * b[p], d[2 * p + 1] += 1ll * (t - m) * b[p];
		b[p] = 0;
	}
	if (m >= l) update(l, r, c, s, m, 2 * p);
	if (m < r) update(l, r, c, m + 1, t, 2 * p + 1);
	d[p] = d[2 * p] + d[2 * p + 1];
}

LL getsum(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) { return d[p];}
	int m = (s + t) >> 1;
	if (b[p] && s != t) {
		b[2 * p] += b[p]; b[2 * p + 1] += b[p];
		d[2 * p] += 1ll * (m - s + 1) * b[p], d[2 * p + 1] += 1ll * (t - m) * b[p];
		b[p] = 0;
	}
	LL ret = 0;
	if (m >= l) ret += getsum(l, r, s, m, 2 * p);
	if (m < r) ret += getsum(l, r, m + 1, t, 2 * p + 1);
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	build(1, 1, n);
	for (int i = 1, f, x, y, k; i <= m; ++i) {
		scanf("%d%d%d", &f, &x, &y);
		if (f == 1) {
			scanf("%d", &k);
			update(x, y, k, 1, n, 1);
		}
		else printf("%lld\n", getsum(x, y, 1, n, 1));
	}
	return 0;
}