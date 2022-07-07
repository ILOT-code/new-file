//参照博客，在给出的图上进行尝试构造。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const LL mod = 1000000007;
const int maxn = 100000 + 10;
int T, kase, n, k;
LL dp[maxn + 10][50 + 5];

void init() {
	memset(dp, 0, sizeof(dp));
	dp[2][1] = 1;
	for (int i = 3; i <= maxn; ++i)
		for (int j = 1; j <= min(50, i); ++j) {
			dp[i][j] = (dp[i - 1][j] * (i - 1) % mod * (i - 1) % mod +
			            dp[i - 1][j] * (i - 1) % mod +
			            dp[i - 2][j - 1] * (1LL * i * (i - 1) / 2 % mod) % mod * (i - 1) % mod) % mod;
		}
}

int main() {
	scanf("%d", &T);
	init();
	while (T--) {
		scanf("%d%d", &n, &k);
		printf("Case %d: %lld\n", ++kase, dp[n][k]);
	}
	return 0;
}