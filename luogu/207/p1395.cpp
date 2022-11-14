#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000 + 10;
int n, sons[maxn], f[maxn];
vector<int> G[maxn];

void dfs(int x, int fa, int d) {
	sons[x] = 1; f[1] += d;
	for (int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i];
		if (v == fa) continue;
		dfs(v, x, d + 1);
		sons[x] += sons[v];
	}
}

void dp(int x, int fa) {
	if (x != 1)f[x] = f[fa] + n - 2 * sons[x];
	for (int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i];
		if (v == fa) continue;
		dp(v, x);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0, 0);
	dp(1, 0);
	int ans = f[1], idx = 1;
	for (int i = 1; i <= n; ++i)
		if (f[i] < ans) {
			ans = f[i];
			idx = i;
		}
	printf("%d %d\n", idx, ans);
	return 0;
}
