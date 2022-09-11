#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int maxn = 100000 + 10;
int T, kase, n, dp[maxn];
vector<PII> G[maxn];

LL ans;
void dfs(int u, int f) {
	dp[u] = 1;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i].first, w = G[u][i].second;
		if (v == f) continue;
		dfs(v, u);

		ans += min(dp[v], n - dp[v]) * w * 2;
		dp[u] += dp[v];
	}
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1; i <= n - 1; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(PII(v, w));
			G[v].push_back(PII(u, w));
		}

		ans = 0;
		dfs(1, 0);
		printf("Case #%d: %lld\n", ++kase, ans);
	}
	return 0;
}
