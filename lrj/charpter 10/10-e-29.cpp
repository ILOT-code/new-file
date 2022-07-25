//现在的排名与过去的排名是一个二分图的匹配关系。
//dp[i][j]，表示在这次与过去的前i名中，有j个没有匹配。
//由对称性的关系，j在现在的图与过去的图中是相等的。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
const long long mod = 1000000007;
int T, kase;
long long dp[maxn][maxn];
char s[maxn];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		dp[0][0] = 1;
		for (int i = 1; i <= len; ++i)
			for (int j = 0; j <= i; ++j) {
				dp[i][j] = 0;
				if (s[i] == 'U')
					dp[i][j] = (dp[i - 1][j] * j + (j ? dp[i - 1][j - 1] : 0)) % mod;
				else if (s[i] == 'D')
					dp[i][j] = (dp[i - 1][j + 1] * (j + 1) * (j + 1) + dp[i - 1][j] * j) % mod;
				else dp[i][j] = dp[i - 1][j];
			}
		printf("Case %d: %lld\n", ++kase, dp[len][0]);
	}
	return 0;
}

