#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
int T, n, w, h;
int d[maxn << 2], b[maxn << 2], H[maxn], cnt;

struct Point {
	int x, y, v;
} po[maxn];
bool cmp1(const Point& a, const Point& b) {return a.x < b.x;};
bool cmp2(const Point& a, const Point& b) {return a.y < b.y;};
void build(int s, int t, int p) {
	b[p] = d[p] = 0;
	if (s == t) return;
	int m = (s + t) >> 1;
	build(s, m, 2 * p); build(m + 1, t, 2 * p + 1);
}
void pushdown(int s, int t, int p) {
	if (s == t || b[p] == 0) return;
	d[2 * p] += b[p]; b[2 * p] += b[p];
	d[2 * p + 1] += b[p]; b[2 * p + 1] += b[p];
	b[p] = 0;
}
void update(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {
		d[p] += c; b[p] += c;
		return;
	}
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	if (m >= l) update(l, r, c, s, m, 2 * p);
	if (m < r) update(l, r, c, m + 1, t, 2 * p + 1);
	d[p] = max(d[2 * p], d[2 * p + 1]);
}
/*int getmax(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) return d[p];
	int m = (s + t) >> 1;
	pushdown(s, t, p);
	int ans = 0;
	if (m >= l) ans = max(ans, getmax(l, r, s, m, 2 * p));
	if (m < r) ans = max(ans, getmax(l, r, m + 1, t, 2 * p + 1));
	return ans;
}*/
void getpos(int& l, int& r, int p) {
	int y = po[p].y;
	l = lower_bound(H + 1, H + 1 + cnt, y) - H;
	r = lower_bound(H + 1, H + 1 + cnt, y + h) - H - 1;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		cnt = 0;
		scanf("%d%d%d", &n, &w, &h);
		for (int i = 1; i <= n; ++i) scanf("%d%d%d", &po[i].x, &po[i].y , &po[i].v);
		sort(po + 1, po + 1 + n, cmp2);
		for (int i = 1; i <= n; ++i) if (i == 1 || po[i].y != po[i - 1].y) H[++cnt] = po[i].y;
		build(1, cnt, 1);
		sort(po + 1, po + 1 + n, cmp1);
		int L = 1, up = 1, ready = 1, ans = 0;

		while (ready <= n) {
			while (ready <= n && po[ready].x < po[L].x + w) {
				int l , r; getpos(l, r, ready);
				update(l, r, po[ready].v, 1, cnt, 1);
				ready++;
			}
			while (up < ready && po[up].x < po[L].x) {
				int l, r; getpos(l, r, up);
				update(l, r, -po[up].v, 1, cnt, 1);
				up++;
			}
			ans = max(ans, d[1]);
			L++;
		}
		printf("%d\n", ans);
	}
	return 0;
}