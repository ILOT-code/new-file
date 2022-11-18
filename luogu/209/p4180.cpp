#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 10;
const int maxm = 300000 + 10;
int n, m, p[maxn], cnt, h[maxn];
LL sum;
int d[maxn], fa[maxn][20], maxw[maxn][20], Log[maxn];
bool vis[maxm];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]);}
struct Edge1 {
	int u, v, w;
	bool operator<(const Edge1& rhs) { return w < rhs.w; }
} e1[maxm];

struct Edge2 {
	int v, w, nex;
} e2[2 * maxn];

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
		cnt1++; p[x] = y;
		vis[i] = 1;
		sum += 1LL * e1[i].w;
		add_edge(e1[i].u, e1[i].v, e1[i].w); add_edge(e1[i].v, e1[i].u, e1[i].w);
		if (cnt1 == n - 1) break;
	}
}


void dfs(int x, int f, int weight) {
	d[x] = d[f] + 1, fa[x][0] = f, maxw[x][0] = weight;
	for (int k = 1; k <= Log[d[x]]; ++k)
		fa[x][k] = fa[fa[x][k - 1]][k - 1], maxw[x][k] = max(maxw[x][k - 1], maxw[fa[x][k - 1]][k - 1]);
	for (int i = h[x]; i; i = e2[i].nex) {
		int v = e2[i].v;
		if (v == f) continue;
		dfs(v, x, e2[i].w);
	}
}
int LCA(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	int tmpx = -1, tmpy = -1;
	while (d[x] > d[y]) tmpx = max(tmpx, maxw[x][Log[d[x] - d[y]]]), x = fa[x][Log[d[x] - d[y]]];
	if (x == y) return tmpx;

	for (int k = Log[d[x]]; k >= 0; --k)
		if (fa[x][k] != fa[y][k]) {
			tmpx = max(tmpx, maxw[x][k]), tmpy = max(tmpy, maxw[y][k]);
			x = fa[x][k], y = fa[y][k];
		}
	tmpx = max(tmpx, maxw[x][0]), tmpy = max(tmpy, maxw[y][0]);
	return max(tmpx, tmpy);
}

void update(int& a, int& b, int t) {
	if (a < t) b = a, a = t;
	else if (b < t && t < a) b = t;
}
int ask(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	int tmp[4] = { -1, -1, -1, -1};
	while (d[x] > d[y]) {
		update(tmp[0], tmp[1], maxw[x][Log[d[x] - d[y]]]);
		x = fa[x][Log[d[x] - d[y]]];
	}
	if (x == y) return tmp[1];

	for (int k = Log[d[x]]; k >= 0; --k)
		if (fa[x][k] != fa[y][k]) {
			update(tmp[0], tmp[1], maxw[x][k]);
			update(tmp[2], tmp[3], maxw[y][k]);
			x = fa[x][k], y = fa[y][k];
		}
	update(tmp[0], tmp[1], maxw[x][0]);
	update(tmp[2], tmp[3], maxw[y][0]);
	sort(tmp, tmp + 4);
	if (tmp[2] != tmp[3]) return tmp[2];
	return tmp[1];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &e1[i].u, &e1[i].v, &e1[i].w);
	for (int i = 1; i <= n; ++i) p[i] = i;
	Log[1] = 0, Log[2] = 1;
	for (int i = 3; i <= n; ++i) Log[i] = Log[i / 2] + 1;
	krus();
	dfs(1, 0, -1);

	int ans = 0x7f7f7f7f;
	for (int i = 0; i < m; ++i)if (!vis[i]) {
			if (e1[i].u == e1[i].v) continue;
			int t = LCA(e1[i].u, e1[i].v);
			if (t != e1[i].w) ans = min(ans, e1[i].w - t);
			else {
				t = ask(e1[i].u, e1[i].v);
				if (t == -1) continue;
				ans = min(ans, e1[i].w - t);
			}
		}
	printf("%lld\n", sum + 1LL * ans);
	return 0;
}
