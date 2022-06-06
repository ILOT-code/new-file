#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
const int INF = 0x3f3f3f3f;
int n, a[maxn], b[maxn], dp[2][2][maxn];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);
		for (int i = 0; i < n; ++i) dp[0][0][i] = dp[0][1][i] = 0;
		int t = 1;
		for (int len = 2; len <= n; ++len) {
			for (int i = 0; i <= n - len; ++i) {
				int j = i + len - 1;
				dp[0][t][i] = min(dp[0][t ^ 1][i + 1] + a[i + 1] - a[i], dp[1][t ^ 1][i + 1] + a[j] - a[i]);
				if (dp[0][t][i] >= b[i]) dp[0][t][i] = INF;
				dp[1][t][i] = min(dp[0][t ^ 1][i] + a[j] - a[i], dp[1][t ^ 1][i] + a[j] - a[j - 1]);
				if (dp[1][t][i] >= b[j]) dp[1][t][i] = INF;
			}
			t ^= 1;
		}
		int ans = min(dp[0][t ^ 1][0], dp[1][t ^ 1][0]);
		if (ans >= INF) printf("No solution\n");
		else printf("%d\n", ans);
	}
	return 0;

}