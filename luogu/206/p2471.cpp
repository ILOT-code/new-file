#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;
const int maxn = 50000 + 10;
PII a[maxn];
int n, m;
int d[maxn << 2], Y[maxn];
void build(int s, int t, int p) {
	if (s == t) {d[p] = a[s].se; return;}
	int m = (s + t) >> 1;
	build(s, m, 2 * p); build(m + 1, t, 2 * p + 1);
	d[p] = max(d[2 * p], d[2 * p + 1]);
}

int getmax(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) return d[p];
	int m = (s + t) >> 1;
	int ret = 0;
	if (m >= l) ret = max(ret, getmax(l, r, s, m, 2 * p));
	if (m < r) ret = max(ret, getmax(l, r, m + 1, t, 2 * p + 1));
	return ret;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].fi, &a[i].se), Y[i] = a[i].fi;
	build(1, n, 1);
	scanf("%d", &m);
	for (int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if (x >= y) {printf("false\n"); continue;}
		int t = 0;
		int lx = lower_bound(Y + 1, Y + 1 + n, x) - Y, fx = x == Y[lx];
		int ly = lower_bound(Y + 1, Y + 1 + n, y) - Y, fy = y == Y[ly];
		if (lx + fx <= ly - 1) t = getmax(lx + fx, ly - 1, 1, n, 1);

		if ((fy && t >= a[ly].se) || (fx && fy && a[lx].se < a[ly].se) || (fx && t >= a[lx].se)) printf("false\n");
		else if (!fx || !fy || y - x != ly - lx) printf("maybe\n");
		else printf("true\n");
	}
	return 0;
}
