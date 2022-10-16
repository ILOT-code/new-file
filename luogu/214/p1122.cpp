#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 16000 + 10;
const int INF = 0x3f3f3f3f;
int n, w[maxn], d[maxn];
vector<int> e[maxn];
void dfs(int u, int fa) {
	d[u] = w[u];
	for (int i = 0; i < e[u].size(); ++i) {
		int v = e[u][i];
		if (v == fa) continue;
		dfs(v, u);
		if (d[v] > 0) d[u] += d[v];
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	int ans = -INF;
	for (int i = 1; i <= n; ++i) ans = max(ans, d[i]);
	printf("%d\n", ans);
	return 0;
}