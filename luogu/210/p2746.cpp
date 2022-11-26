#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;

int n, t, h[maxn];
int dfn[maxn], low[maxn], clo[maxn], cnt, tot;
int d_in[maxn], d_out[maxn];
struct Edge {
	int u, v, nex;
} e[maxn * maxn];

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
			v = st.top();
			clo[v] = tot;
			st.pop();
		} while (v != u);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1, tmp; i <= n; ++i)
		while (~scanf("%d", &tmp) && tmp) add_edge(i, tmp);

	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= t; ++i) {
		int u = e[i].u, v = e[i].v;
		if (clo[u] == clo[v]) continue;
		else d_in[clo[v]]++, d_out[clo[u]]++;
	}
	int ret_in = 0, ret_out = 0;
	for (int i = 1; i <= tot; ++i) {
		if (d_in[i] == 0) ret_in++;
		if (d_out[i] == 0) ret_out++;
	}
	printf("%d\n", ret_in);
	printf("%d\n", tot == 1 ? 0 : max(ret_in, ret_out));
	return 0;
}