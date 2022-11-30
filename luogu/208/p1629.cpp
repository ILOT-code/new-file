#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
#define fi first
#define se second
const int maxn = 1000 + 5;
const int maxm = 100000 + 5;
const int INF = 0x3f3f3f3f;

int n, m, t, h[2 * maxn];
struct Edge {
	int u, v, w, nex;
} e[2 * maxm];

void add_edge(int u, int v, int w) {
	e[++t] = Edge{u, v, w, h[u]};
	h[u] = t;
}

int d[2 * maxn];
priority_queue<PII, vector<PII>, greater<PII>> q;
void dijkstra() {
	for (int i = 1; i <= 2 * n; ++i) d[i] = INF;
	d[1] = 0, d[1 + n] = 0; q.push(PII(0, 1)), q.push(PII(0, 1 + n));
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
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w); add_edge(v + n, u + n, w);
	}
	dijkstra();
	int ans = 0;
	for (int i = 1; i <= 2 * n; ++i) ans += d[i];
	printf("%d\n", ans);
	return 0;
}