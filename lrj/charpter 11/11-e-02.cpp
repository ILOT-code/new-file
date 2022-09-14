#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<double, int> PDI;

const int maxn = 100 + 5;
const int INF = 0x3f3f3f3f;
int kase, n, vis[maxn];
double d[maxn];

struct Node {
	int x, y, z, r;
	Node(int x = 0, int y = 0, int z = 0, int r = 0): x(x), y(y), z(z), r(r) {}
} nodes[maxn];

double dist(int u, int v) {
	double dis = sqrt((nodes[u].x - nodes[v].x) * (nodes[u].x - nodes[v].x) + (nodes[u].y - nodes[v].y) * (nodes[u].y - nodes[v].y)
	                  + (nodes[u].z - nodes[v].z) * (nodes[u].z - nodes[v].z));
	int dr = nodes[u].r + nodes[v].r;
	if (dis <= dr) return 0;
	return (dis - dr) * 10;
}

int main() {
	while (~scanf("%d", &n) && n != -1) {
		int x, y, z, r;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &x, &y, &z, &r);
			nodes[i] = Node(x, y, z, r);
		}
		scanf("%d%d%d", &x, &y, &z); nodes[n] = Node(x, y, z);
		scanf("%d%d%d", &x, &y, &z); nodes[n + 1] = Node(x, y, z);

		priority_queue<PDI, vector<PDI>, greater<PDI>> Q;
		for (int i = 0; i < n + 2; ++i) d[i] = INF;
		d[n] = 0;
		memset(vis, 0, sizeof(vis));
		Q.push(PDI(0, n));
		while (!Q.empty()) {
			PDI head = Q.top(); Q.pop();
			int u = head.second;
			if (vis[u]) continue;
			if (u == n + 1) break;
			vis[u] = true;
			for (int v = 0; v < n + 2; ++v) {
				if (v == u) continue;
				if (d[v] > d[u] + dist(u, v)) {
					d[v] = d[u] + dist(u, v);
					Q.push(PDI(d[v], v));
				}
			}
		}
		int ans = round(d[n + 1]);
		printf("Cheese %d: Travel time = %d sec\n", ++kase, ans);
	}
}