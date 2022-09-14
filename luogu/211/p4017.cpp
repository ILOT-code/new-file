#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
const int mod = 80112002;
const int INF = 0x3f3f3f3f;

int n, m, d[maxn];
bool vis[maxn], g[maxn][maxn], ntoop[maxn];
int dfs(int u) {
	if (vis[u]) return d[u];
	vis[u] = 1;
	for (int v = 1; v <= n; ++v)
		if (g[u][v]) d[u] = (d[u] + dfs(v)) % mod;
	if (d[u] == 0) return d[u] = 1;
	return d[u];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		g[u][v] = 1;
		ntoop[v] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (!ntoop[i]) ans = (ans + dfs(i)) % mod;
	printf("%d\n", ans);
	return 0;
}