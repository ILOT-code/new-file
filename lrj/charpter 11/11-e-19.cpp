#include<vector>
#include<queue>
#include<map>
#include<string>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<iomanip>
using namespace std;

const double eps = 1e-10;
const double INF = 0x3f3f3f3f;
const int maxn = 2000 + 5;

struct Edge {
	int from, to, m, t, p, d;
	Edge(int u, int v, int m, int t, int p, int d): from(u), to(v), m(m), t(t), p(p), d(d) {}
};

struct SPFA {
	vector<Edge> edges;
	vector<int> G[maxn];
	int start, end;
	int inq[maxn];
	double dist[maxn][60];

	void init() {
		for (int i = 0; i < maxn; ++i) G[i].clear();
		edges.clear();
	}

	void AddEdge(int u, int v, int m, int t, int p, int d) {
		edges.push_back(Edge(u, v, m, t, p, d));
		G[u].push_back(edges.size() - 1);
	}

	void spfa(int n) {
		for (int i = 0; i < n; ++i) inq[i] = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < 60; ++j)
				dist[i][j] = (i == start ? 0 : INF);
		queue<int> Q; Q.push(start); inq[start] = 1;
		bool reach = false;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop(); inq[u] = 0;
			for (int i = 0; i < G[u].size(); ++i) {
				Edge& e = edges[G[u][i]];
				bool update = false;
				for (int j = 0; j < 60; ++j) {
					double ans = (e.m - j + 60) % 60;
					ans += (100.0 - e.p) / 100 * (e.t + dist[u][(e.m + e.t) % 60]);
					for (int k = 1; k <= e.d; ++k)
						ans += e.p / 100.0 / e.d * (e.t + k + dist[u][(e.m + e.t + k) % 60]);
					if (ans < dist[e.to][j] - eps) {dist[e.to][j] = ans; update = true;}
				}
				if (update && !inq[e.to]) {Q.push(e.to); inq[e.to] = 1;}
				if (update && e.to == end) reach = 1;
			}
		}
		if (!reach) cout << "IMPOSSIBLE" << endl;
		else {
			double ans = INF;
			for (int i = 0; i < 60; ++i) ans = min(ans, dist[end][i]);
			cout << setprecision(10) << ans << endl;
		}
	}
};

SPFA g;
map<string, int> IDcache;
int ID(string &s) {
	if (IDcache.count(s)) return IDcache[s];
	return IDcache[s] = IDcache.size();
}

int main() {
	int T, n, m, t, p, d;
	cin >> T;
	while (T--) {
		IDcache.clear(); g.init();
		string name1, name2;
		cin >> name1 >> name2;
		g.start = ID(name2), g.end = ID(name1);
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> name1 >> name2 >> m >> t >> p >> d;
			g.AddEdge(ID(name2), ID(name1), m, t, p, d);
		}
		g.spfa(IDcache.size());
	}
	return 0;
}