#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100000 + 5;
const int INF = 0x3f3f3f3f;
int n, b;
struct Gra {
	int s, p;
	bool operator<(const Gra& rhs) const {return p < rhs.p;}
} g[maxn];

int main() {
	scanf("%d%d", &n, &b);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &g[i].s, &g[i].p);
	sort(g + 1, g + 1 + n);

	int ans = INF;
	int r = lower_bound(g + 1, g + 1 + n, Gra{0, b}) - g, l = r - 1;
	bool flag = 1;
	for (int i = l, j = r; i >= 1; --i) {
		while (j <= n && g[j].p - g[i].p > g[j].s) j++;
		if (j > n) break;
		int t = g[j].p - g[i].p - g[i].s;
		if (t <= 0) {flag = 0; break;}
		ans = min(ans, t);
	}

	for (int i = r, j = l; i <= n; ++i) {
		while (j >= 1 && g[i].p - g[j].p > g[j].s) j--;
		if (j < 1) break;
		int t = g[i].p - g[j].p - g[i].s;
		if (t <= 0) {flag = 0; break;}
		ans = min(ans, t);
	}
	if (flag == 0) printf("0\n");
	else if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}