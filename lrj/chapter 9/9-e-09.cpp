//分两步dp
//注意：safe可能为0,此时safe为分母会出现runtim eerror。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 100 + 5;
const int maxm = 30 + 5;
int n, m, safe, p[maxm],dp[maxn];

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0] = INF;
    for (int i = 1; i <= m; ++i)
        for (int j = n; j > 0; --j)
            for (int k = 1; k <= min(p[i], j); ++k)
                dp[j] = max(dp[j], min(dp[j - k], p[i] / k));

    safe = dp[n];
    if(safe == 0) return;
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = n; j > 0; --j)
            for (int k = 1; k <= min(p[i] / safe, j); ++k)
                dp[j] = min(dp[j], dp[j - k] + p[i]);
}

int main() {
    while (~scanf("%d%d", &n, &m) && n && m) {
        for (int i = 1; i <= m; ++i) scanf("%d", &p[i]);
        solve();
        printf("%d %d\n", safe, dp[n]);
    }
    return 0;
}