#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, q;
int h[maxn], fa[maxn][19], d[maxn], cnt, Log[maxn];

struct Edge {
	int v, nex;
	Edge(int v = 0, int nex = 0): v(v), nex(nex) {}
} e[2 * maxn];

void add_edge(int u, int v) {
	e[++cnt] = Edge(v, h[u]);
	h[u] = cnt;
}

void dfs(int x, int f) {
	fa[x][0] = f, d[x] = d[f] + 1;
	for (int k = 1; k <= Log[d[x]]; ++k)
		fa[x][k] = fa[fa[x][k - 1]][k - 1];
	for (int i = h[x]; i; i = e[i].nex)
		if (e[i].v != f) dfs(e[i].v, x);
}

int LCA(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	while (d[x] > d[y])
		x = fa[x][Log[d[x] - d[y]]];
	if (x == y) return x;
	for (int k = Log[d[x]]; k >= 0; --k)
		if (fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}

int dist(int x, int y) {
	int c = LCA(x, y);
	return abs(d[x] - d[c]) + abs(d[y] - d[c]);
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	Log[1] = 0; Log[2] = 1;
	for (int i = 3; i <= n; ++i) Log[i] =  Log[i / 2] + 1;
	dfs(1, 0);

	for (int i = 1, a, b, c, d; i <= q; ++i) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int x = LCA(a, b), y = LCA(c, d);
		if (dist(c, x) + dist(d, x) == dist(c, d) || dist(a, y) + dist(b, y) == dist(a, b)) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}