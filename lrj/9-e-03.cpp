#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1 << 20;
const int maxn = 20 + 5;
int kase = 1, n, m, k, a[maxn][maxn];
int cnt[maxn][maxn];
int f[maxn][maxn][maxn][maxn], vis[maxn][maxn][maxn][maxn];

int getnum(int d, int r, int u, int l) {
	return cnt[d][r] - cnt[d][l] - cnt[u][r] + cnt[u][l];
}

int dp(int d, int r, int u, int l) {
	int &ans = f[d][r][u][l];
	if (vis[d][r][u][l] == kase) return ans;
	vis[d][r][u][l] = kase;
	ans = INF;
	if (getnum(d, r, u, l) == 1) return ans = 0;
	for (int i = l + 1; i < r; ++i)if (getnum(d, i, u, l) && getnum(d, r, u, i))
			ans = min(ans, d - u + dp(d, i, u, l) + dp(d, r, u, i));
	for (int i = u + 1; i < d; ++i)if (getnum(i, r, u, l) && getnum(d, r, i, l))
			ans = min(ans, r - l + dp(i, r, u, l) + dp(d, r, i, l));
	return ans;
}
int main() {
	while (~scanf("%d%d%d", &n, &m, &k) && n) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < k; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[x][y] = 1;
		}
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j) {
				if (i == 0 || j == 0) cnt[i][j] = 0;
				else cnt[i][j] = cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1] + a[i][j];
			}
		printf("Case %d: %d\n", kase++, dp(n, m, 0, 0));
	}
	return 0;
}