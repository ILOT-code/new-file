#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 5;
const int maxm = 500000 + 5;
const int INF = 0x7f7f7f7f;
int T, n, m, cnt, h[maxn];
LL open[maxn];
struct Edge {
	int u, v, w, nex;
} e[2 * maxm];
struct Node {
	LL d;
	int u;
	Node(LL d  = 0, int u = 0): d(d), u(u) {}
	bool operator>(const Node& rhs) const { return d > rhs.d; }
};
void add_edge(int u, int v, int w) {
	e[++cnt] = Edge{u, v, w, h[u]};
	h[u] = cnt;
}
bool vis[maxn];
LL dis[maxn];
priority_queue<Node, vector<Node>, greater<Node>> q;
void dijkstra() {
	memset(vis, 0, sizeof(vis));
	memset(dis, INF, sizeof(dis));
	dis[1] = 0; q.push(Node(0, 1));
	while (!q.empty()) {
		int u = q.top().u; q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = h[u]; i; i = e[i].nex) {
			int v = e[i].v;
			LL w = e[i].w;
			if (dis[u] + w < open[v]) w = open[v] - dis[u];
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push(Node(dis[v], v));
			}
		}
	}
	printf("%lld\n", dis[n]);
}
int main() {
	scanf("%d", &T);
	while (T--) {
		memset(h, 0, sizeof(h)); cnt = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) {
			int u, v, w; scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w); add_edge(v, u, w);
		}
		for (int i = 2; i <= n; ++i) scanf("%lld", &open[i]);
		dijkstra();
	}
	return 0;
}
