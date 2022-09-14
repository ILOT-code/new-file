#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
const int INF = 0x3f3f3f3f;
int n, m, p[maxn];
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x;}

struct Edge {
	int u, v, d;
	Edge(int u, int v, int d): u(u), v(v), d(d) {}
	bool operator<(const Edge& rhs) { return d < rhs.d; }
};
vector<Edge> edges;

int solve() {
	sort(edges.begin(), edges.end());
	int ans = INF;
	for (int L = 0; L < m; ++L) {
		for (int i = 1; i <= n; ++i) p[i] = i;
		int cnt = 0;
		for (int R = L; R < m; ++R) {
			int u = find(edges[R].u), v = find(edges[R].v);
			if (u != v) {
				p[u] = v;
				if (++cnt == n - 1) {ans = min(ans, edges[R].d - edges[L].d); break;}
			}
		}
	}
	if (ans == INF) ans = -1;
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		edges.clear();
		for (int i = 0, u, v, d; i < m; ++i) {
			scanf("%d%d%d", &u, &v, &d);
			edges.push_back(Edge(u, v, d));
		}
		printf("%d\n", solve());
	}
	return 0;
}