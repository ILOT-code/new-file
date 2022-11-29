#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10000 + 5;
const int maxm = 50000 + 5;
const LL INF = 1e20;
int n, m, b, f[maxn];
int T, H[maxn];

struct Edge {
	int u, v, w, nex;
} e[2 * maxm];

void add_edge(int u, int v, int w) {
	e[++T] = Edge{u, v, w, H[u]};
	H[u] = T;
}
LL d[maxn];
bool vis[maxn];
queue<int> q;
bool SPFA(int lim) {
	while (!q.empty()) q.pop();
	for (int i = 1; i <= n; ++i) vis[i] = 0, d[i] = INF;
	vis[1] = 1, d[1] = 0, q.push(1);

	while (!q.empty()) {
		int u = q.front(); vis[u] = 0, q.pop();
		for (int i = H[u]; i; i = e[i].nex) {
			int v = e[i].v, w = e[i].w;
			if (f[v] > lim) continue;
			if (d[v] > d[u] + 1ll * w) {
				d[v] = d[u] + 1ll * w;
				if (!vis[v]) q.push(v), vis[v] = 1;
			}
		}
	}
	return d[n] <= b;
}
int main() {
	scanf("%d%d%d", &n, &m, &b);
	int L = 0, R = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", &f[i]), R = max(R, f[i]);
	L = max(f[1], f[n]);
	for (int i = 1; i <= m; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w); add_edge(v, u, w);
	}
	if (!SPFA(R)) {printf("AFK\n"); return 0;}
	while (L < R) {
		int mid = (L + R) >> 1;
		if (SPFA(mid)) R = mid;
		else L = mid + 1;
	}
	printf("%d\n", L);
	return 0;
}