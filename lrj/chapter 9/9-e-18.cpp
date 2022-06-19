//我觉得这种取前5位的做法并不严格，我无法证明这是最优的，也未在网上找到证明。
//但是发现了此篇博客，驳斥了这种做法：https://www.cnblogs.com/jionkitten/p/12984866.html
//能够举出反例，则这确实是有问题的。
#include<cstdio>
#include<cstring>
#include<algorithm>
#define now d[i]
using namespace std;

const int maxn = 200 + 15;
int n, m, g, p[maxn][maxn], d[maxn], b[maxn][6], f[2][6][6][6][6];
struct Node {
	int id, x;
	bool operator<(const Node &rhs) const {
		return x > rhs.x;
	}
} temp[maxn];

void dp() {
	memset(f, -1, sizeof(f));
	int t = 0;
	memset(f[t], 0, sizeof(f[t]));

	int wj = -5, wk = -5, wl = -5, wq = -5, ans = 0;
	for (int i = 1; i <= g + 10; ++i)
		if (d[i]) {
			ans = 0;
			memset(f[t^1],-1,sizeof(f[t^1]));
			for (int j = 1; j <= 5; ++j)
				for (int k = 1; k <= 5; ++k)
					for (int l = 1; l <= 5; ++l)
						for (int q = 1; q <= 5; ++q)
							if (f[t][j][k][l][q] != -1)
								for (int id = 1; id <= 5; ++id) {
									if ((i - wj <= 4 && b[now][id] == b[d[wj]][j]) || (i - wk <= 4 && b[now][id] == b[d[wk]][k]) ||
									    (i - wl <= 4 && b[now][id] == b[d[wl]][l]) || (i - wq <= 4 && b[now][id] == b[d[wq]][q])) continue;
									f[t ^ 1][k][l][q][id] = max(f[t ^ 1][k][l][q][id], f[t][j][k][l][q] + p[now][b[now][id]]);
									ans = max(ans, f[t ^ 1][k][l][q][id]);
								}
			wj = wk, wk = wl, wl = wq, wq = i, t ^= 1;
		}
	printf("%.2lf\n", ans * 1.0 / 100);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &g);
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j) scanf("%d", &p[i][j]);
		for (int i = 1; i <= g + 10; ++i) scanf("%d", &d[i]);

		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) temp[j].id = j, temp[j].x = p[i][j];
			sort(temp + 1, temp + 1 + n);
			for (int j = 1; j <= 5; ++j) b[i][j] = temp[j].id;
		}
		dp();
	}
	return 0;
}