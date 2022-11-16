#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 1e6 + 10;
int n, col[maxn], cnt, h[maxn], tot[maxn], now[maxn], sons[maxn], endpos[maxn], endcnt[maxn];
LL ans1[maxn], ans2[maxn];

struct Edge {
	int v, nex;
	Edge(int v = 0, int nex = 0): v(v), nex(nex) {}
} e[2 * maxn];

void add_edge(int u, int v) {
	e[++cnt] = Edge(v, h[u]);
	h[u] = cnt;
}

void dfs(int x, int fa) {
	sons[x] = 1;
	int t = now[col[x]];
	int flag = 0, pos = 0;
	bool isend = 0;
	for (int i = h[x]; i; i = e[i].nex) {
		int v = e[i].v;
		if (v == fa) continue;
		int last = now[col[x]];
		dfs(v, x);
		if (last != now[col[x]]) flag++, pos = v;
		if (tot[col[x]] == 1) ans1[x] += 1LL * sons[x] * sons[v];
		sons[x] += sons[v];
	}
	if (tot[col[x]] == 1) ans1[x] += 1LL * sons[x] * (n - sons[x]);

	if (flag == 0 || (flag == 1 && t == 0 && now[col[x]] == tot[col[x]] - 1)) isend = true;
	if (isend) {
		if (endcnt[col[x]] == 0) endpos[col[x]] = x;
		else if (endcnt[col[x]] == 1) {
			int p = pos ? n - sons[pos] : sons[x];
			ans2[col[x]] = 1LL * p * sons[endpos[col[x]]];
		}
		endcnt[col[x]]++;
	}
	now[col[x]]++;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &col[i]);
		endpos[col[i]] = i;
		tot[col[i]]++;
	}
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		if (tot[i] == 0)
			printf("%lld\n", 1LL * n * (n - 1) >> 1);
		else if (tot[i] == 1)
			printf("%lld\n", ans1[endpos[i]]);
		else if (endcnt[i] == 2)
			printf("%lld\n", ans2[i]);
		else puts("0");
	}
	return 0;
}