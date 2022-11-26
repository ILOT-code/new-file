#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int maxm = 50000 + 5;

int n, m, t, h[maxn];
int dfn[maxn], low[maxn], clo[maxn], sum[maxn], cnt, tot;
int d[maxn];

struct Edge {
	int u, v, nex;
} e[maxm];

void add_edge(int u, int v) {
	e[++t] = Edge{u, v, h[u]};
	h[u] = t;
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

	if (low[u] == dfn[u]) {
		tot++;
		int v;
		do {
			sum[tot]++;
			v = st.top();
			clo[v] = tot;
			st.pop();
		} while (v != u);
	}
}


int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		add_edge(u, v);
	}

	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);

	for (int i = 1; i <= m; ++i) {
		int u = e[i].u, v = e[i].v;
		if (clo[u] == clo[v]) continue;
		d[clo[u]]++;
	}
	int start = 0, pos = 0, ans = 0;
	for (int i = 1; i <= tot; ++i)
		if (!d[i]) start++, pos = i;

	if (start != 1) ans = 0;
	else ans = sum[pos];
	printf("%d\n", ans);
	return 0;
}