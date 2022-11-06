#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int n, m, q, a[maxn], d[maxn << 2], f[maxn << 2];

struct Ques {
	int q, idx, ans;
	Ques(int q = 0, int idx = 0, int ans = 0): q(q), idx(idx), ans(ans) {}
} Q[maxn];
struct Point {
	int h, idx;
	Point(int h = 0, int idx = 0): h(h), idx(idx) {}
} po[maxn];
bool cmp3(Point a, Point b) {
	if (a.h == b.h) return a.idx < b.idx;
	else return a.h < b.h;
}
bool cmp4(Point a, Point b) {return a.idx < b.idx;}
bool cmp1(Ques a, Ques b) {return a.q < b.q;}
bool cmp2(Ques a, Ques b) {return a.idx < b.idx;}
void build(int s, int t, int p) {
	if (s == t) {d[p] = po[s].h, f[p] = s; return;}
	int m = (s + t) >> 1;
	build(s, m, 2 * p); build(m + 1, t, 2 * p + 1);
	if (d[2 * p] <= d[2 * p + 1]) d[p] = d[2 * p], f[p] = f[2 * p];
	else d[p] = d[2 * p + 1], f[p] = f[2 * p + 1];
}

void add(int l, int s, int t, int p) {
	if (s == t && s == l) {d[p]++; return;}
	int m = (s + t) >> 1;
	if (l <= m) add(l, s, m, 2 * p);
	else add(l, m + 1, t, 2 * p + 1);
	if (d[2 * p] <= d[2 * p + 1]) d[p] = d[2 * p], f[p] = f[2 * p];
	else d[p] = d[2 * p + 1], f[p] = f[2 * p + 1];
}
void solve(int l, int r) {
	int ret = r - l + 1;
	int bo = 1;
	while (ret) {
		while (bo <= m && po[bo].h == po[bo + 1].h) bo++;
		if(bo == m) 

	}

}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1, t; i <= n; ++i) scanf("%d", &t), a[t]++;
	for (int i = 1; i <= m; ++i) po[i].h = a[i], po[i].idx = i;
	build(1, m, 1);
	for (int i = 1; i <= q; ++i) scanf("%d", &Q[i].q), Q[i].idx = i;
	sort(Q + 1, Q + 1 + q, cmp1);
	int ready = n + 1, rq = 1;
	while (rq <= q) {
		sort(po + 1, po + 1 + m, cmp3);
		solve(ready, Q[rq].q);
		sort(po + 1, po + 1 + m, cmp4);
		build(1, m, 1);
	}
	sort(Q + 1, Q + 1 + q, cmp2);
	for (int i = 1; i <= q; ++i) printf("%d\n", Q[i].ans);
	return 0;
}