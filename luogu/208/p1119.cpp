#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
const int INF = 0x3f3f3f3f;
int n, m, q, t[maxn], d[maxn][maxn];

void update(int k) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main() {
	memset(d, INF, sizeof(d));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) d[i][i] = 0, scanf("%d", &t[i]);
	for (int i = 1; i <= m; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		d[u][v] = d[v][u] = w;
	}
	scanf("%d", &q);
	int p = 0;
	while (q--) {
		int u, v, now; scanf("%d%d%d", &u, &v, &now);
		while (p < n && t[p] <= now) {
			update(p);
			p++;
		}
		if (t[u] > now || t[v] > now) printf("-1\n");
		else printf("%d\n", d[u][v] == INF ? -1 : d[u][v]);
	}
	return 0;
}