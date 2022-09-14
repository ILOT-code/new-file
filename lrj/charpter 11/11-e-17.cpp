#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, leaf[maxn];
vector<int> G[maxn];

void dfs(int u, int fa) {
	for (auto v : G[u])
		if (v != fa) dfs(v, u);
	if (G[u].size() == 1) leaf[m++] = u;
}
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1, u, v; i <= n - 1; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}

		m = 0;
		dfs(1, 0);
		printf("%d\n", (m + 1) / 2);
		int mid = m / 2;
		for (int i = 0; i < mid; ++i) printf("%d %d\n", leaf[i], leaf[i + mid]);
		if (m & 1) printf("%d %d\n", leaf[0], leaf[m - 1]);
	}
	return 0;
}
