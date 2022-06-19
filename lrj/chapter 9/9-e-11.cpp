#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int mod = 1e9 + 7;
const int maxk = 10 + 2;
const int maxn = 400 + 5;
int T, n, k;
int dp[maxn][(1 << (maxk - 1)) - 1];
int pali[maxk][(1 << (maxk - 1)) - 1];

void init() {
	pali[1][0] = pali[1][1] = 1;
	for (int i = 2; i <= 11; ++i)
		for (int j = 0; j < (1 << i); ++j) {
			int t1 = 1 & j, t2 = j >> (i - 1);
			if (t1 == t2 && (i - 2 == 0 || pali[i - 2][(j & ((1 << (i - 1)) - 1)) >> 1] == i - 2))
				pali[i][j] = i;
			else pali[i][j] = max(pali[i - 1][j >> 1], pali[i - 1][j & ((1 << (i - 1)) - 1)]);
		}
}

int main() {
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= k + 1; ++i)
			for (int j = 0; j <= (1 << i) - 1; ++j)
				if (pali[i][j] < k) dp[i][j] = 1;
				else dp[i][j] = 0;
		for (int i = k + 2; i <= n; ++i)
			for (int j = 0; j <= (1 << (k + 1)) - 1; ++j)
				if (pali[k + 1][j] >= k) dp[i][j] = 0;
				else dp[i][j] = (dp[i - 1][j >> 1] + dp[i - 1][(j >> 1) + (1 << k)]) % mod;

		int ans = 0, t = min(n, k + 1);
		for (int j = 0; j <= (1 << t) - 1; ++j)
			ans = (ans + dp[n][j]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}