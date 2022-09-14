#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
const int INF = 0x3f3f3f3f;
struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
};

struct EdmondsKarp {
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	int a[maxn];
	int p[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	int Maxflow(int s, int t) {
		int flow = 0;
		for (;;) {
			memset(a, 0, sizeof(a));
			queue<int> Q;
			Q.push(s);
			a[s] = INF;
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				for (int i = 0; i < G[x].size(); i++) {
					Edge& e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = min(a[x], e.cap - e.flow);
						Q.push(e.to);
					}
				}
				if (a[t]) break;
			}
			if (!a[t]) break;
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += a[t];
				edges[p[u] ^ 1].flow -= a[t];
			}
			flow += a[t];
		}
		return flow;
	}
};
EdmondsKarp g;

int n, m, link[maxn][maxn];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		g.init(2 * n);
		memset(link, 0, sizeof(link));
		for (int i = 0; i < n; ++i) g.AddEdge(i, i + n, 1);
		for (int i = 0, j; i < m; ++i) {
			char str[20];
			scanf("%s", str);
			int u = 0, v = 0;
			for (j = 1; str[j] != ','; ++j) u = u * 10 + (str[j] - '0');
			for (j++; str[j] != ')'; ++j) v = v * 10 + (str[j] - '0');
			g.AddEdge(u + n, v, INF);
			g.AddEdge(v + n, u, INF);
		}

		vector<Edge> tmpt(g.edges);
		int ans = INF;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if (!link[i][j]) {
					ans = min(ans, g.Maxflow(i + n, j));
					g.edges = tmpt;
				}
		if (ans >= INF) ans = n;
		printf("%d\n", ans);
	}
	return 0;
}