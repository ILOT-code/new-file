#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
#define fi first
#define se second
const int maxn = 100000 + 5;
const int maxm = 500000 + 5;
const int INF = 0x3f3f3f3f;
int n, m, s, t, h[maxn];

struct Edge {
	int u, v, w, nex;
} e[maxm];

void add_edge(int u, int v, int w) {
	e[++t] = Edge{u, v, w, h[u]};
	h[u] = t;
}

int d[maxn];
priority_queue<PII, vector<PII>, greater<PII>> q;
void dijkstra(int s) {
	for (int i = 1; i <= n; ++i) d[i] = INF;
	d[s] = 0; q.push(PII(0, s));

	while (!q.empty()) {
		int u = q.top().se, w = q.top().fi; q.pop();
		if (w > d[u]) continue;
		for (int i = h[u]; i; i = e[i].nex) {
			int v = e[i].v;
			if (d[v] > d[u] + e[i].w) {
				d[v] = d[u] + e[i].w;
				q.push(PII(d[v], v));
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= m; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
	}
	dijkstra(s);
	for (int i = 1; i <= n; ++i) printf("%d ", d[i]);
	return 0;
}