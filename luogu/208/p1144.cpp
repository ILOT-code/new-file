#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
const int maxm = 2000000 + 5;
const int mod = 100003;
int n, m, d[maxn], f[maxn], t, h[maxn];
bool vis[maxn];

struct Edge {
	int u, v, nex;
} e[maxm];

void add_edge(int u, int v) {
	e[++t] = Edge{u, v, h[u]};
	h[u] = t;
}
void bfs() {
	queue<int> q;
	q.push(1); vis[1] = 1, d[1] = 0, f[1] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = h[u]; i; i = e[i].nex) {
			int v = e[i].v;
			if (!vis[v]) d[v] = d[u] + 1, vis[v] = 1, q.push(v);
			if (d[v] == d[u] + 1) f[v] = (f[v] + f[u]) % mod;
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		add_edge(u, v); add_edge(v, u);
	}
	bfs();
	for (int i = 1; i <= n; ++i) printf("%d\n", f[i]);
	return 0;
}