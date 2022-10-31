#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 300000 + 10;
int n, m, t[maxn];

inline int lowbit(int x) {return x & (-x);}
void add(int x) {
	while (x <= n) {
		t[x] += 1;
		x += lowbit(x);
	}
}
LL getsum(int x) {
	LL ret = 0;
	while (x) {
		ret += t[x];
		x -= lowbit(x);
	}
	return ret;
}

struct Data {
	int h, p;
	Data(int h = 0, int p = 0) : h(h), p(p) {}
	bool operator<(const Data& rhs) {return h < rhs.h;}
} a[maxn];
int cnt;
struct Point {
	int l, r;
	Point(int l = 0, int r = 0): l(l), r(r) {}
	bool operator<(const Point& rhs) {return r < rhs.r;}
} points[2 * maxn];

struct Ques {
	int l, r, t;
	Ques(int l = 0, int r = 0, int t = 0): l(l), r(r), t(t) {}
	bool operator<(const Ques& rhs) {return r < rhs.r;}
} ques[maxn];
void addpair(int x, int y) {
	int X = min(x, y), Y = max(x, y);
	points[++cnt] = Point(X, Y);
}
int main() {
	scanf("%d%d", &n, &m);
	if (n == 1) {printf("0\n"); return 0;}
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].h), a[i].p = i;
	sort(a + 1, a + 1 + n);
	addpair(a[1].p, a[2].p); addpair(a[n - 1].p, a[n].p);
	for (int i = 2; i < n; ++i) {
		int t1 = abs(a[i - 1].h - a[i].h), t2 = abs(a[i + 1].h - a[i].h);
		if (t1 <= t2) addpair(a[i - 1].p, a[i].p);
		if (t2 <= t1) addpair(a[i + 1].p, a[i].p);
	}
	sort(points + 1, points + 1 + cnt);

	for (int i = 1; i <= m; ++i) scanf("%d%d", &ques[i].l, &ques[i].r), ques[i].t = i;
	sort(ques + 1, ques + 1 + m);
	LL ans = 0;
	for (int i = 1, j = 1; i <= m; ++i) {
		while (points[j].r <= ques[i].r && j <= cnt) { add(points[j++].l); }
		ans += 1ll * (j - 1 - getsum(ques[i].l - 1)) * ques[i].t;
	}
	printf("%lld\n", ans);
	return 0;
}