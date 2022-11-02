#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200000 + 10;
int n, m, d[maxn << 2];
bool a[maxn], b[maxn << 2];

void build(int s, int t, int p) {
	if (s == t) {d[p] = a[s]; return;}
	int m = (s + t) >> 1;
	build(s, m, 2 * p); build(m + 1, t, 2 * p + 1);
	d[p] = d[2 * p] + d[2 * p + 1];
}
void pushdown(int s, int t, int p) {
	if (s == t || b[p] == 0) return;
	int m = (s + t) >> 1;
	d[2 * p] = m - s + 1 - d[2 * p], b[2 * p] ^= 1;
	d[2 * p + 1] = t - m - d[2 * p + 1], b[2 * p + 1] ^= 1;
	b[p] = 0;
}
void update(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] = t - s + 1 - d[p];
		b[p] ^= 1;
		return;
	}

	int m = (s + t) >> 1;
	pushdown(s, t, p);
	if (m >= l) update(l, r, s, m, 2 * p);
	if (m < r) update(l, r, m + 1, t, 2 * p + 1);
	d[p] = d[2 * p] + d[2 * p + 1];
}

int getsum(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) return d[p];
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	int ret = 0;
	if (m >= l) ret += getsum(l, r, s, m, 2 * p);
	if (m < r) ret += getsum(l, r, m + 1, t, 2 * p + 1);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, t; i <= n; ++i) scanf("%1d", &t), a[i] = t;
	build(1, n, 1);
	for (int i = 1, f, x, y; i <= m; ++i) {
		scanf("%d%d%d", &f, &x, &y);
		if (f == 0) update(x, y, 1, n, 1);
		else printf("%d\n", getsum(x, y, 1, n, 1));
	}
	return 0;
}