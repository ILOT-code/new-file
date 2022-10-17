#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 3000 + 10;
const int INF = 0x3f3f3f3f;
int n, m, t, head[maxn], val[maxn], d[maxn][maxn];
struct Edge {
	int u, v, w, next;
	Edge(int u = 0, int v = 0, int w = 0, int next = 0): u(u), v(v), w(w), next(next) {}
} edges[maxn];

void AddEdge(int u, int v, int w) {
	edges[++t] = Edge(u, v, w, head[u]);
	head[u] = t;
}
int dp(int root) {
	d[root][0] = 0;
	if (head[root] == 0) { d[root][1] = val[root]; return 1;}
	int sum = 0, t;
	for (int i = head[root]; i; i = edges[i].next) {
		int v = edges[i].v; t = dp(v); sum += t;
		for (int j = sum; j > 0; --j) {
			for (int k = 0; k <= t; ++k)
				d[root][j] = max(d[root][j], d[v][k] - (k == 0 ? 0 : edges[i].w) + d[root][j - k]);
		}
	}
	return sum;
}
int main() {
	scanf("%d%d", &n, &m);
	memset(d, -INF, sizeof(d));
	for (int i = 1, k; i <= n - m; ++i) {
		scanf("%d", &k);
		for (int j = 0, v, w; j < k; ++j) {
			scanf("%d%d", &v, &w);
			AddEdge(i, v, w);
		}
	}
	for (int i = 1; i <= m; ++i) scanf("%d", &val[n - m + i]);
	dp(1);
	for (int i = m; i >= 1; --i) if (d[1][i] >= 0) {
			printf("%d\n", i);
			return 0;
		}
}