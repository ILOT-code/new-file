#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1120 + 5;
const int maxk = 14 + 1;
int n, m;
int cnt, vis[maxn + 1], p[maxn + 1], sum[maxn + 1], dp[maxn + 1][maxk + 1];

void init() {
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) p[cnt++] = i;
		for (int j = 0; j < cnt && i * p[j] < maxn; ++j) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
	sum[0] = p[0];
	for (int i = 1; i < cnt; ++i) sum[i] = sum[i - 1] + p[i];
}
void solve() {
	dp[0][0] = 1;
	for (int i = 0; i < cnt; ++i)
		for (int j = min(maxn, sum[i]); j >= p[i]; --j)
			for (int k = 1; k < maxk; ++k)
				dp[j][k] += dp[j - p[i]][k - 1];
}
int main() {
	init();
	solve();
	while (~scanf("%d%d", &n, &m) && n) {
		printf("%d\n", dp[n][m]);
	}
	return 0;
}