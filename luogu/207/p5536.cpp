//易得，必须包括直径的中点。如果不包括，那么有距离大于直径的一半。在包括直径的情况下，距离都必小于等于直径的一半。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100000 + 10;
int n, k;
int h[maxn], cnt, d[maxn], fa[maxn], d1[maxn];

struct Edge {
	int v, nex;
	Edge(int v = 0, int nex = 0): v(v), nex(nex) {}
} e[2 * maxn];

void add_edge(int u, int v) {
	e[++cnt] = Edge(v, h[u]);
	h[u] = cnt;
}

void dfs(int x) {
	for (int i = h[x]; i; i = e[i].nex) {
		if (e[i].v == fa[x]) continue;
		fa[e[i].v] = x; d[e[i].v] = d[x] + 1;
		dfs(e[i].v);
	}
}

int dfs1(int x, int f) {
	int deep = 0;
	for (int i = h[x]; i; i = e[i].nex) {
		if (e[i].v == f) continue;
		d[e[i].v] = d[x] + 1;
		deep = max(deep, dfs1(e[i].v, x));
	}
	return d1[x] = deep + 1;
}


int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}

	d[1] = 0; dfs(1);
	int L = 1, R = 1;
	for (int i = 1; i <= n; ++i) if (d[i] > d[R]) R = i;
	memset(fa, 0, sizeof(fa));
	d[R] = 0; dfs(R);
	for (int i = 1; i <= n; ++i) if (d[i] > d[L]) L = i;
	int mid = L;
	for (; ; mid = fa[mid]) if (d[mid] == d[L] / 2) break;
	d[mid] = 0; dfs1(mid, 0);
	sort(d1 + 1, d1 + 1 + n);
	printf("%d\n", d1[n - k]);
	return 0;
}