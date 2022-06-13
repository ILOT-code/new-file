//很容易证明，排序后，如果某个筷子是做某一套的a,b的话，则另一根筷子必然相邻。
//现在麻烦的一点是，新加入的筷子如果做c怎么办？只要逆着进行dp,每一次保证必有完整的一套即可。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
const int maxk = 1000 + 10;
const int INF = 0x3f3f3f3f;
int n, k, a[maxn], dp[maxn][maxk];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &k, &n);
        k += 8;
        for (int i = n; i > 0; --i) scanf("%d", &a[i]);
        memset(dp, INF, sizeof(dp));
        for (int i = 0; i <= n; ++i) dp[i][0] = 0;

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= i / 3; ++j)
                dp[i][j] = min(dp[i - 1][j], dp[i - 2][j - 1] + (a[i] - a[i - 1]) * (a[i] - a[i - 1]));

        printf("%d\n", dp[n][k]);
    }
    return 0;
}