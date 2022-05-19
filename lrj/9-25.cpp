//这题代码仓库中的代码是错误的，它用到的结论无法严格证明。并且，在CSDN上还找到了一组反例。
//严谨的做法是维护一个单调队列，维护前后两个指针。
//9-25b中的单调队列写的更好。
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
        if (abs(h[0] - h[n-1]) > (n - 1) * d) {
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
            int l = 1, r = 1;
            que[0] = -1;
            for (int j = 0; j < nx; ++j) {
                int temp = que[r - 1] + 1;
                while (temp < nx &&(r == l || x[temp] <= x[j] + d)) {
                    while (r > l && dp[t][temp] <= dp[t][que[r - 1]]) r--;
                    que[r++] = temp;
                    temp++;
                }
                while (l < r && x[que[l]] < x[j] - d) l++;
                if (l == r) dp[t ^ 1][j] = INF;
                else dp[t ^ 1][j] = dp[t][que[l]] + abs(x[j] - h[i]);
            }
            t ^= 1;
        }
        for (int i = 0; i < nx; i++)
            if (x[i] == h[n - 1]) printf("%lld\n", dp[t][i]);
    }
}