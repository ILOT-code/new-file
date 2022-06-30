#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long LL;

int n, m;
LL dp[64 + 5][64 + 5][100 + 5];

int main() {
    int T, kase = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        if (n & 1 || !m)  {printf("Case %d: 0\n", ++kase); continue;}
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for (int i = 0, temp = 1 % m; i < n; ++i, temp = (2 * temp) % m)
            for (int j = 0; j <= i; ++j)
                for (int k = 0; k < m; ++k) {
                    if (i + 1 != n) dp[i + 1][j][k] += dp[i][j][k];
                    dp[i + 1][j + 1][(k + temp) % m] += dp[i][j][k];
                }
        printf("Case %d: %lld\n", ++kase, dp[n][n / 2][0]);
    }
    return 0;
}