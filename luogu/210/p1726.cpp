#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int maxm = 50000 + 5;

int n, m, t, h[maxn];
int dfn[maxn], low[maxn], clo[maxn], sum[maxn], cnt, tot, maxs;

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
		maxs = max(maxs, sum[tot]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v, f; scanf("%d%d%d", &u, &v, &f);
		add_edge(u, v);
		if (f == 2) add_edge(v, u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);

	printf("%d\n", maxs);
	for (int i = 1; i <= n; ++i)
		if (sum[clo[i]] == maxs) {
			for (int j = i; j <= n; ++j)
				if (clo[j] == clo[i]) printf("%d ", j);
			break;
		}
	return 0;
}
