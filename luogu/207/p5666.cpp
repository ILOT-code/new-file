//在dfs2到达结点x时，树状数组c1中存放的是，所有边的分割中，另一颗不含x的数的节点数。
//c2在前后相差的是，所有x的子树中的边的上诉描述。
//每个dfs2 x,计算完了x与它父亲的那条边隔开是否会让rt成为重心，并且计算了x成为重心的次数*x.
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 300000 + 10;
int n, rt, s[maxn], g[maxn], u, v, z[maxn];
LL ans, c1[maxn], c2[maxn];
vector<int> e[maxn];
void add(LL* c, int x, int k) {
	while (x <= n + 1) c[x] += k, x += x & -x;
}
LL ask(LL* c, int x) {
	LL ret = 0;
	while (x) ret += c[x], x -= x & -x;
	return ret;
}

void dfs1(int x, int f) {
	s[x] = 1, g[x] = 0;
	bool fg = 1;
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f) continue;
		dfs1(y, x);
		s[x] += s[y];
		g[x] = max(g[x], s[y]);
		if (s[y] > (n >> 1)) fg = 0;
	}
	if (n - s[x] > (n >> 1)) fg = 0;
	if (fg) rt = x;
}

void dfs2(int x, int f) {
	if (x != rt) {
		add(c2, s[x], 1);
		add(c1, s[x], -1); add(c1, n - s[x], 1);
		ans += x * ask(c1, n - 2 * g[x]);
		ans -= x * ask(c1, n - 2 * s[x] - 1);
		ans += x * ask(c2, n - 2 * g[x]);
		ans -= x * ask(c2, n - 2 * s[x] - 1);
		if (!z[x] && z[f]) z[x] = 1;
		ans += rt * (s[x] <= n - 2 * s[z[x] ? v : u]);
	}
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f) continue;
		dfs2(y, x);
	}

	if (x != rt) {
		add(c1, s[x], 1); add(c1, n - s[x], -1);
		ans -= x * ask(c2, n - 2 * g[x]);
		ans += x * ask(c2, n - 2 * s[x] - 1);
	}
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), e[x].push_back(y), e[y].push_back(x);
	ans = 0;
	dfs1(1, 0);
	dfs1(rt, 0);
	u = v = 0;
	for (int i = 0; i < e[rt].size(); i++) {
		int x = e[rt][i];
		if (s[x] > s[v]) v = x;
		if (s[v] > s[u]) swap(u, v);
	}
	for (int i = 1; i <= n; i++) c1[i] = c2[i] = 0;
	for (int i = 1; i <= n; i++) {z[i] = 0; if (i != rt) add(c1, s[i], 1);}
	z[u] = 1;
	dfs2(rt, 0);
	printf("%lld\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}