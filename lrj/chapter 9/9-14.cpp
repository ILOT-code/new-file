//对树采用递推的方法。
//虽然有多重循环，实际上由于树的特性，每个点最多被用3次，自己被算一次，复杂度仍是O(n).
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int INF = 1 << 20;
vector<int> G[maxn], topo;
int n, p[maxn], d[maxn][3];

void creat_tree(int u, int fa) {
	topo.push_back(u);
	p[u] = fa;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v != fa) creat_tree(v, u);
	}
}

void dp() {
	for (int i = topo.size() - 1; i >= 0; --i) {
		int u = topo[i];
		d[u][0] = 1; d[u][1] = 0;
		for (int j = 0; j < G[u].size(); ++j) {
			int v = G[u][j];
			if (v == p[u]) continue;
			d[u][0] += min(d[v][0], d[v][1]);
			d[u][1] += d[v][2];
		}
		d[u][2] = INF;
		for (int j = 0; j < G[u].size(); ++j) {
			int v = G[u][j];
			if (v == p[u]) continue;
			d[u][2] = min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
		}
	}
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
		topo.clear();
		creat_tree(0, -1);
		dp();
		printf("%d\n", min(d[0][0], d[0][2]));
		scanf("%d", &n);
	}
	return 0;
}