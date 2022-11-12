#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, a[maxn], d[maxn << 2];

void build(int s, int t, int p) {
	if (s == t) {d[p] = a[s]; return;}
	int m = (s + t) >> 1;
	build(s, m, 2 * p); build(m + 1, t, 2 * p + 1);
	d[p] = d[2 * p] + d[2 * p + 1];
}

void update(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] = (r - l + 1) * c;
		return;
	}
	int m = (s + t) >> 1;
	if (m >= l) update(l, r, c, s, m, 2 * p);
	if (m < r) update(l, r, c, m + 1, t, 2 * p + 1);
	d[p] = d[2 * p] + d[2 * p + 1];
}
int getsum(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) return d[p];
	int m = (s + t) >> 1;
	int ret = 0;
	if (m >= l) ret += getsum(l, r, s, m, 2 * p);
	if (m < r) ret += getsum(l, r, m + 1, t, 2 * p + 1);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	build(1, n, 1);
	int p = 0;
	for (int i = 0, f, x, y; i < m; ++i) {
		scanf("%d", &f);
		if (f == 1) {p--; continue;}
		if (f == 2) {p++; continue;}
		if (f == 3) {
			scanf("%d%d", &x, &y);
			update(x, x, y, 1, n, 1);
			continue;
		}
		if (f == 4) {
			scanf("%d", &x);
			p %= n;
			int t1 = (x - p + n - 1) % n + 1;
			int t2 = (1 - p + n - 1) % n + 1;
			if (t1 >= t2) printf("%d\n", getsum(t2, t1, 1, n, 1));
			else printf("%d\n", getsum(1, t1, 1, n, 1) + getsum(t2, n, 1, n, 1));
		}

	}
	return 0;
}