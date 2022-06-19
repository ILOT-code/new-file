#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;

const LL  INF = (1LL << 60);
const int maxn = 100 + 5;
const int maxx = maxn * maxn * 2;
int n, que[maxx];
LL d, h[maxn], x[maxx], dp[2][maxx];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &n, &d);
        for (int i = 0; i < n; ++i) scanf("%lld", &h[i]);
        if (abs(h[0] - h[n - 1]) > (n - 1) * d) {
            printf("impossible\n");
            continue;
        }
        int nx = 0;
        for (int i = 0; i < n; ++i)
            for (int j = -n + 1; j <= n - 1; ++j)
                x[nx++] = h[i] + j * d;
        sort(x, x + nx);
        nx = unique(x, x + nx) - x;

        int t = 0;
        for (int i = 0; i < nx; ++i) {
            dp[t][i] = INF;
            if (x[i] == h[0]) dp[0][i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int l = 0, r = 0;
            int tr = 0;
            for (int j = 0; j < nx; ++j) {
                while (tr < nx && x[tr] <= x[j] + d) {
                    while (r > l && dp[t][tr] <= dp[t][que[r - 1]]) r--;
                    que[r++] = tr++;
                }
                while (l < r && x[que[l]] < x[j] - d) l++;
                if (l == r) dp[t ^ 1][j] = INF;
                else dp[t ^ 1][j] = dp[t][que[l]] + abs(x[j] - h[i]);
            }
            t ^= 1;
        }
        int pos = lower_bound(x, x + nx, h[n - 1]) - x;
        printf("%lld\n", dp[t][pos]);
    }
}