#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1 << 30;
const int maxn = 50 + 5;
const int maxT = 200 + 5;
int n, T, m, d, t[maxn], dp[maxT][maxn];
bool has_train[maxT][maxn][2];

int main() {
	int kase = 0;
	while (~scanf("%d%d", &n, &T) && n) {
		memset(has_train, 0, sizeof(has_train));
		for (int i = 1; i < n; ++i) scanf("%d", &t[i]);
		scanf("%d", &m);
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &d);
			for (int i = 1; i < n; ++i) {
				if (d <= T) has_train[d][i][0] = 1;
				d += t[i];
			}
		}
		scanf("%d", &m);
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &d);
			for (int i = n; i > 1; --i) {
				if (d <= T) has_train[d][i][1] = 1;
				d += t[i - 1];
			}
		}

		for (int i = 1; i < n; ++i) dp[T][i] = INF;
		dp[T][n] = 0;
		for (int i = T - 1; i >= 0; --i)
			for (int j = 1; j <= n; ++j) {
				dp[i][j] = dp[i + 1][j] + 1;
				if (j < n && has_train[i][j][0] && i + t[j] <= T)
					dp[i][j] = min(dp[i][j], dp[i + t[j]][j + 1]);
				if (j > 1 && has_train[i][j][1] && i + t[j - 1] <= T)
					dp[i][j] = min(dp[i][j], dp[i + t[j - 1]][j - 1]);
			}

		printf("Case Number %d: ", ++kase);
		if (dp[0][1] >= INF) printf("impossible\n");
		else printf("%d\n", dp[0][1]);
	}
	return 0;

}