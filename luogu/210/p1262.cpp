#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 3000 + 10;
const int maxm = 8000 + 10;
const int INF = 0x3f3f3f3f;
int n, p, m, val[maxn], t, h[maxn], T, H[maxn];
int cnt, tot, dfn[maxn], low[maxn], clo[maxn], w[maxn], d[maxn];
struct Edge {
	int u, v, nex;
} e[maxm], E[maxm];

void add_edge(int u, int v) {
	e[++t] = Edge{u, v, h[u]};
	h[u] = t;
}
void Add_edge(int u, int v) {
	E[++T] = Edge{u, v, H[u]};
	H[u] = T;
}

stack<int> st;
void tarjan(int u) {
	dfn[u] = low[u] = ++cnt;
	st.push(u);
	for (int i = h[u]; i; i = e[i].nex) {
		int v = e[i].v;
		if (clo[v]) continue;
		if (!dfn[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		tot++;
		w[tot] = INF;
		int v;
		do {
			v = st.top();
			st.pop();
			clo[v] = tot;
			w[tot] = min(w[tot], val[v]);
		} while (v != u);
	}
}
bool V[maxn];
void dfs(int u) {
	V[u] = 1;
	for (int i = H[u]; i; i = E[i].nex) {
		int v = E[i].v;
		if (V[v]) continue;
		dfs(v);
	}
}
int solve() {
	for (int i = 1; i <= tot; ++i)
		if (!V[i] && w[i] < INF) dfs(i);
	for (int i = 1; i <= n; ++i)
		if (!V[clo[i]]) return i;
}
int main() {
	scanf("%d%d", &n, &p);
	memset(val, INF, sizeof(val));
	for (int i = 1; i <= p; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		val[x] = y;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);

	for (int i = 1; i <= t; ++i) {
		int u = e[i].u, v = e[i].v;
		if (clo[u] == clo[v]) continue;
		d[clo[v]]++;
		Add_edge(clo[u], clo[v]);
	}
	int ans = 0;
	bool flag = true;
	for (int i = 1; i <= tot; ++i)
		if (d[i] == 0) {
			if (w[i] >= INF) {flag = false; break;}
			ans += w[i];
		}
	if (flag) printf("YES\n%d\n", ans);
	else printf("NO\n%d\n", solve());
	return 0;
}