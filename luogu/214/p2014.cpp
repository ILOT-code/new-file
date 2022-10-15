#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 300 + 5;
int n, m, dp[maxn][maxn], val[maxn];
vector<int>sons[maxn];

void dfs(int u) {
	for (int i = 0; i < sons[u].size(); ++i) {
		int v = sons[u][i];
		dfs(v);
		for (int j = m; j >= 0; --j)
			for (int k = 0; k < j; ++k)
				dp[u][j] = max(dp[u][j], dp[v][k] + dp[u][j - k - 1] + val[v]);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, f, w; i <= n; ++i) {
		scanf("%d%d", &f, &w);
		sons[f].push_back(i);
		val[i] = w;
	}
	dfs(0);
	printf("%d\n", dp[0][m]);
	return 0;
}
