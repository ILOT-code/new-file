#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int INF = 0x3f3f3f3f;
int n, a[maxn], b[maxn], dp[2][maxn][maxn];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);

		for (int len = 2; len <= n; ++len)
			for (int i = 0; i <= n - len; ++i) {
				int j = i + len - 1;
				dp[0][i][j] = min(dp[0][i + 1][j] + a[i + 1] - a[i], dp[1][i + 1][j] + a[j] - a[i]);
				if (dp[0][i][j] >= b[i]) dp[0][i][j] = INF;

				dp[1][i][j] = min(dp[0][i][j - 1] + a[j] - a[i], dp[1][i][j - 1] + a[j] - a[j - 1]);
				if (dp[1][i][j] >= b[j]) dp[1][i][j] = INF;
			}
		int ans = min(dp[0][0][n - 1], dp[1][0][n - 1]);
		if (ans >= INF) printf("N0 solution\n");
		else printf("%d\n", ans);
	}
	return 0;

}