#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
const int maxm = 50000 + 10;
const int INF = 0x3f3f3f3f;
int n, m, q, p[maxn];
int cnt, h[maxn];
int Log[maxn], d[maxn], fa[maxn][20], minw[maxn][20];
bool vis[maxn];
struct Edge1 {
	int u, v, w;
	bool operator<(Edge1 &rhs) {return w > rhs.w;}
} e1[maxm];

struct Edge2 {
	int v, w, nex;
} e2[2 * maxn];

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

void init() {
	for (int i = 1; i <= n; ++i) p[i] = i;
	Log[1] = 0; Log[2] = 1;
	for (int i = 3; i <= n; ++i) Log[i] = Log[i / 2] + 1;
}
void add_edge(int u, int v, int w) {
	e2[++cnt] = Edge2{v, w, h[u]};
	h[u] = cnt;
}

void krus() {
	sort(e1, e1 + m);
	int cnt1 = 0;
	for (int i = 0; i < m; ++i) {
		int x = find(e1[i].u), y = find(e1[i].v);
		if (x == y) continue;
		cnt1++;
		p[x] = y;
		add_edge(e1[i].u, e1[i].v, e1[i].w); add_edge(e1[i].v, e1[i].u, e1[i].w);
		if (cnt1 == n - 1) break;
	}
}

void dfs(int x, int f, int weight) {
	vis[x] = 1; d[x] = d[f] + 1;
	fa[x][0] = f; minw[x][0] = weight;

	for (int  k = 1; k <= Log[d[x]]; ++k) {
		fa[x][k] = fa[fa[x][k - 1]][k - 1];
		minw[x][k] = min(minw[x][k - 1], minw[fa[x][k - 1]][k - 1]);
	}

	for (int i = h[x]; i; i = e2[i].nex) {
		int v = e2[i].v, w = e2[i].w;
		if (v == f) continue;
		dfs(v, x, w);
	}
}

int LCA(int x, int y) {
	if (find(x) != find(y)) return -1;
	if (d[x] < d[y]) swap(x, y);
	int tmpx = INF, tmpy = INF;
	while (d[x] > d[y]) {
		tmpx = min(tmpx, minw[x][Log[d[x] - d[y]]]);
		x = fa[x][Log[d[x] - d[y]]];
	}
	if (x == y) return tmpx;

	for (int k = Log[d[x]]; k >= 0; --k) {
		if (fa[x][k] != fa[y][k]) {
			tmpx = min(tmpx, minw[x][k]); tmpy = min(tmpy, minw[y][k]);
			x = fa[x][k], y = fa[y][k];
		}
	}
	tmpx = min(tmpx, minw[x][0]), tmpy = min(tmpy, minw[y][0]);
	return min(tmpx, tmpy);
}
int main() {
	scanf("%d%d", &n, &m); init();
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &e1[i].u, &e1[i].v, &e1[i].w);
	krus();
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 0, INF);
	scanf("%d", &q);
	for (int i = 1, x, y; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		printf("%d\n", LCA(x, y));
	}
	return 0;
}