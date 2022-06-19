#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 10000 + 5;
const int INF = 0x3f3f3f3f;
int n, c1, c2;
int dp[maxn][4];
vector<int> G[maxn];

void dfs(int u, int fa) {
	dp[u][0] = dp[u][3] = 0;
	dp[u][1] = c1, dp[u][2] = c2;
	int d = INF, sum = 0;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v == fa) continue;
		dfs(v, u);
		int t = min(dp[v][0], min(dp[v][1], dp[v][2]));
		dp[u][0] += dp[v][1];
		dp[u][1] += t;
		dp[u][2] += min(t, dp[v][3]);
		dp[u][3] += t;
		sum += t; //sum = dp[u][3];
		d = min(d, dp[v][2] - t);
	}
	dp[u][1] = min(dp[u][1], sum + d);
}
int main() {
	while (~scanf("%d%d%d", &n, &c1, &c2) && n) {
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1, -1);
		printf("%d\n", min(dp[1][0], min(dp[1][1], dp[1][2])));
	}
	return 0;
}