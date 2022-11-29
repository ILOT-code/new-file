#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;
const int maxn = 150 + 5;
const int INF = 0x3f3f3f3f;
int n, g[maxn][maxn], clo[maxn], tot;
double d[maxn][maxn];
double max_p[maxn], max_t[maxn];
PII po[maxn];
void dfs(int u) {
	clo[u] = tot;
	for (int i = 1; i <= n; ++i)
		if (g[u][i] && !clo[i]) dfs(i);
}
double cla(int i, int j) { return sqrt((po[i].fi - po[j].fi) * (po[i].fi - po[j].fi) + (po[i].se - po[j].se) * (po[i].se - po[j].se)); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &po[i].fi, &po[i].se);
	for (int i = 1; i <= n; ++i) {
		char s[maxn]; scanf("%s", s + 1);
		for (int j = 1; j <= n; ++j) {
			g[i][j] = s[j] == '1';
			if (g[i][j] || i == j) d[i][j] = cla(i, j);
			else d[i][j] = INF;
		}
	}

	for (int i = 1; i <= n; ++i)
		if (!clo[i]) tot++, dfs(i);

	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (clo[i] != clo[j]) continue;
			max_p[i] = max(max_p[i], d[i][j]);
		}
		max_t[clo[i]] = max(max_t[clo[i]], max_p[i]);
	}
	double ans = INF;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j) {
			if (clo[i] == clo[j]) continue;
			double tmp = max(max(max_t[clo[i]], max_t[clo[j]]), cla(i, j) + max_p[i] + max_p[j]);
			ans = min(ans, tmp);
		}

	printf("%.6f\n", ans);
	return 0;
}