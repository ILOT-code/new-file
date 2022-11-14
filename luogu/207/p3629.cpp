#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, k, fa[maxn], d[maxn], ret;
bool vis[maxn];
vector<int> G[maxn];

void dfs(int x) {
	for (int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i];
		if (v == fa[x]) continue;
		if (vis[v] && vis[x]) d[v] = d[x] - 1;
		else d[v] = d[x] + 1;
		fa[v] = x;
		dfs(v);
	}
}

void dp(int x, int f) {
	d[x] = 0;
	for (int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i];
		if (v == f) continue;
		dp(v, x);
		int w = (vis[x] && vis[v]) ? -1 : 1;
		ret = max(ret, d[x]);
		ret = max(ret, d[x] + d[v] + w);
		d[x] = max(d[x], d[v] + w);
	}
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	d[1] = 0; dfs(1);
	int L = 1, R = 1;
	for (int i = 1; i <= n; ++i) if (d[i] > d[R]) R = i;
	memset(fa, 0, sizeof(fa));
	d[R] = 0; dfs(R);
	for (int i = 1; i <= n; ++i) if (d[i] > d[L]) L = i;
	int ans =  2 * (n - 1) - d[L] + 1;
	if (k == 1) { printf("%d\n", ans); return 0; }
	for (int i = L; i; i = fa[i]) vis[i] = 1;
	dp(1, 0);
	printf("%d\n", ans - ret + 1);
	return 0;
}