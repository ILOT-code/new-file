#include<cstdio>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
const int maxm = 100000 + 10;

int n, m, val[maxn], t, T, h[maxn], H[maxn];
int cnt, tot, dfn[maxn], low[maxn], col[maxn], sum[maxn];
int dis[maxn];
bool V[maxn];
struct Edge {
	int u, v, nex;
} e[maxm], E[maxn];

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
		if (col[v]) continue;
		if (!dfn[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		tot++;
		int v;
		do {
			v = st.top();
			st.pop();
			col[v] = tot;
		} while (v != u);
	}
}
queue<int> q;
void SPFA() {
	for (int i = 1; i <= tot; ++i)
		dis[i] = sum[i], V[i] = 1, q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		V[u] = 0;
		for (int i = H[u]; i; i = E[i].nex) {
			int v = E[i].v;
			if (dis[v] < dis[u] + sum[v]) {
				dis[v] = dis[u] + sum[v];
				if (!V[v]) { V[v] = 1; q.push(v);}
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		sum[col[i]] += val[i];
	for (int i = 1; i <= m; ++i) {
		int x = e[i].u, y = e[i].v;
		if (col[x] == col[y]) continue;
		Add_edge(col[x], col[y]);
	}
	SPFA();
	int ans = 0;
	for (int i = 1; i <= tot; ++i) ans = max(ans, dis[i]);
	printf("%d\n", ans);
	return 0;
}