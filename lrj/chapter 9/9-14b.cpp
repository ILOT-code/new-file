//对树采用递归的方法, 对于测试数据可以给出解，但OJ上超时.
//这是因为对于k=2的情况做了大量重复计算，使得复杂度接近与O(n^2).
//可以用记忆化搜索进行优化，使得复杂度变为O(n).
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int INF = 1 << 20;
vector<int> G[maxn];
int n, d[maxn][3];

void creat_tree(int u, int fa) {
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v == fa) {
			G[u][i] = -1;
			continue;
		}
		creat_tree(v, u);
	}
}

int dp(int u, int k) {
	if(d[u][k] != -1) return d[u][k];
	if (k == 0) {
		d[u][k] = 1;
		for (int i = 0; i < G[u].size(); ++i)if (G[u][i] != -1) {
				int v = G[u][i];
				d[u][k] += min(dp(v, 0), dp(v, 1));
			}
	} else if (k == 1) {
		d[u][k] = 0;
		for (int i = 0; i < G[u].size(); ++i)if (G[u][i] != -1) {
				int v = G[u][i];
				d[u][k] += dp(v, 2);
			}
	} else {
		d[u][k] = INF;
		for (int i = 0; i < G[u].size(); ++i)if (G[u][i] != -1) {
				int v = G[u][i];
				d[u][k] = min(d[u][k], dp(u, 1) - dp(v, 2) + dp(v, 0));
			}
	}
	return d[u][k];
}
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) G[i].clear();
		for (int i = 0; i < n - 1; i++) {
			int u, v;
			scanf("%d%d", &u, &v); u--; v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		memset(d,-1,sizeof(d));
		creat_tree(0, -1);
		printf("%d\n", min(dp(0, 0), dp(0, 2)));
		scanf("%d", &n);
	}
	return 0;
}