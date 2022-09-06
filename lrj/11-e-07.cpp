#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;

const int maxn = 500 + 10;
const int gap = 100;
const int INF = 0x3f3f3f3f;

struct Edge {
	int from, to, cost;
	Edge(int u, int v, int d): from(u), to(v), cost(d) {}
};

struct Dijkstra {
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn];
	int d[maxn], p[maxn];
	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}
	void AddEdge(int from, int to, int cost) {
		edges.push_back(Edge(from, to, cost));
		edges.push_back(Edge(to, from, cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	void dijkstra(int s) {
		priority_queue<PII, vector<PII>, greater<PII>> Q;
		for (int i = 0; i < n; ++i) d[i] = INF;
		d[s] = 0;
		memset(done, 0, sizeof(done));
		Q.push(PII(0, s));
		while (!Q.empty()) {
			PII head = Q.top(); Q.pop();
			int u = head.second;
			if (done[u]) continue;
			done[u] = true;
			for (int i = 0; i < G[u].size(); ++i) {
				Edge& e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					Q.push(PII(d[e.to], e.to));
				}

			}
		}
	}
};

Dijkstra g;
int n, k, spend[5];
vector<int> stac[5];

int main() {
	while (~scanf("%d%d", &n, &k)) {
		g.init(n * gap + 1);
		for (int i = 0; i < n; ++i) stac[i].clear();
		for (int i = 0; i < n; ++i) scanf("%d", &spend[i]);

		for (int i = 0; i < n; ++i) {
			while (1) {
				int v; char c;
				scanf("%d%c", &v, &c);
				stac[i].push_back(v);
				if (c == '\n')break;
			}
		}
		for (int i = 0; i < n; ++i)
			for (int j = 1; j < stac[i].size(); ++j)
				g.AddEdge(stac[i][j - 1] + i * gap, stac[i][j] + i * gap, spend[i] * (stac[i][j] - stac[i][j - 1]));

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < stac[i].size(); ++j)
				for (int k = i + 1; k < n; ++k)
					for (int l = 0; l < stac[k].size(); ++l)
						if (stac[i][j] == stac[k][l])
							g.AddEdge(stac[i][j] + i * gap, stac[k][l] + k * gap, 60);
		for (int i = 0; i < n; ++i)
			if (stac[i][0] == 0) g.AddEdge(n * gap, i * gap, 0);
		g.dijkstra(n * gap);

		int ans = INF;
		for (int i = 0; i < n; ++i) ans = min(ans, g.d[k + i * gap]);
		if (ans == INF) printf("IMPOSSIBLE\n");
		else printf("%d\n", ans);
	}
	return 0;
}
