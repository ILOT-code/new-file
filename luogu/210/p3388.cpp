#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20000 + 5;
const int maxm = 100000 + 5;
int n, m, ans, T, H[maxn];
int cnt, dfn[maxn], low[maxn];
bool cut[maxn];

struct Edge {
	int v, nex;
} e[2 * maxm];

void add_edge(int u, int v) {
	e[++T] = Edge{v, H[u]};
	H[u] = T;
}

void tarjan(int u, int fa) {
	int child = 0;
	dfn[u] = low[u] = ++cnt;

	for (int i = H[u]; i; i = e[i].nex) {
		int v = e[i].v;

		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (u != fa && low[v] >= dfn[u]) cut[u] = 1;
			child++;
		}
		else low[u] = min(low[u], dfn[v]);
	}
	if (u == fa && child >= 2) cut[u] = 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		add_edge(u, v); add_edge(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, i);

	for (int i = 1; i <= n; ++i) if (cut[i]) ans++;
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i) if (cut[i]) printf("%d ", i);
	return 0;
}