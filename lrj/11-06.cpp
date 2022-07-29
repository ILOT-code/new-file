#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20;
const int maxm = 100 + 5;
const int INF = 1000000000;
int kase, n, m, t[maxm], dist[1 << maxn], vis[1 << maxn];
char before[maxm][maxn + 5], after[maxm][maxn + 5];
struct Node {
	int bugs, dist;
	Node(int bugs = 0, int dist = 0): bugs(bugs), dist(dist) {}
	bool operator < (const Node& rhs) const { return dist > rhs.dist; }
};

int solve() {
	for (int i = 0; i < 1 << n; ++i) {dist[i] = INF; vis[i] = 0;}
	Node start((1 << n) - 1, 0);
	dist[start.bugs] = 0;
	priority_queue<Node> Q;
	Q.push(start);
	while (!Q.empty()) {
		Node u = Q.top(); Q.pop();
		if (u.bugs == 0) return u.dist;
		if (vis[u.bugs]) continue;
		vis[u.bugs] = 1;
		for (int i = 0; i < m; ++i) {
			bool flag = true;
			for (int j = 0; j < n; ++j) {
				if (before[i][j] == '-' && (u.bugs & (1 << j))) { flag = 0; break;}
				if (before[i][j] == '+' && !(u.bugs & (1 << j))) { flag = 0; break;}
			}
			if (!flag) continue;

			Node u2(u.bugs, u.dist + t[i]);
			for (int j = 0; j < n; ++j) {
				if (after[i][j] == '-') u2.bugs &= ~(1 << j);
				if (after[i][j] == '+') u2.bugs |= (1 << j);
			}
			int &D = dist[u2.bugs];
			if (u2.dist < D) {
				D = u2.dist;
				Q.push(u2);
			}
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		for (int i = 0; i < m; ++i) scanf("%d%s%s", &t[i], before[i], after[i]);
		int ans = solve();
		printf("Product %d\n", ++kase);
		if (ans < 0) printf("Bugs cannot be fixed.\n\n");
		else printf("Fastest sequence takes %d seconds.\n\n", ans);
	}
	return 0;
}