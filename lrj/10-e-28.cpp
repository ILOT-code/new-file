//dp[i][j]表示前i个数是1~i的排列，并且最后一个数是j，且满足要求的个数。
//考虑dp[i][j],若可以增加，它可以由dp[i-1][j'(j'<j)]变换而来，在加入j这个数后，把前面所有>=j的数加一。
//考虑dp[i][j],若可以减少，它可以由dp[i-1][j'(j<=j'<=i-1)]变换而来，在加入j这个数后，把前面所有>=j的数加一。
//在进行这样的变换后，前i个数就成为了1~i的排列，且依旧满足要求。
//因为考虑之前的相邻数a,b，它们满足一种要求，如果a,b都变换了，则一定依旧满足求。
//否则，设a是加1,b没变，那么它们之前的关系只能是a>b，因此依旧没变。
//很容易证明，上面的dp[i][j]与dp[i-1][j']的变换是一个双射关系。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int mod = 1000000007;
const int maxn = 1000 + 5;
int dp[maxn][maxn], sum[maxn][maxn];
char s[maxn];

int main() {
	while (~scanf("%s", s)) {
		int len = strlen(s) + 1;
		dp[1][1] = sum[1][1] = 1;
		for (int i = 2; i <= len; ++i)
			for (int j = 1; j <= i; ++j) {
				dp[i][j] = 0;
				if (s[i - 2] != 'D')
					dp[i][j] = (dp[i][j] + sum[i - 1][j - 1]) % mod;
				if (s[i - 2] != 'I')
					dp[i][j] = (dp[i][j] + sum[i - 1][i - 1] - sum[i - 1][j - 1] + mod) % mod;
				sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
			}
		printf("%d\n", sum[len][len]);
	}
	return 0;
}