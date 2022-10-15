#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int INF = 0x3f3f3f3f;
int n, m, d[maxn][maxn];
bool g[maxn][maxn][65];

int main() {
	scanf("%d%d", &n, &m);
	memset(d, INF, sizeof(d));
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v);
		d[u][v] = 1;
		g[u][v][0] = 1;
	}
	for (int k = 1; k <= 64; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				for (int t = 1; t <= n; ++t)
					if (g[i][j][k - 1] && g[j][t][k - 1]) g[i][t][k] = 1, d[i][t] = 1;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	printf("%d", d[1][n]);
	return 0;
}