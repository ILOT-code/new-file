#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int T, kase, n, p[maxn], v[maxn];
int d[maxn][maxn][maxn][2], vis[maxn][maxn][maxn][2];

int dp(int l, int r, int cnt, int pos) {
    int &ans = d[l][r][cnt][pos];
    if (vis[l][r][cnt][pos] == kase) return ans;
    vis[l][r][cnt][pos] = kase;
    if (cnt == 0) return ans = 0;
    ans = 0;
    int x = (pos == 0 ? l : r);
    for (int i = 0; i < l; ++i)
        ans = max(ans, v[i] - cnt * (p[x] - p[i]) + dp(i, r, cnt - 1, 0));
    for (int i = r + 1; i < n; ++i)
        ans = max(ans, v[i] - cnt * (p[i] - p[x]) + dp(l, i, cnt - 1, 1));
    return ans;
};

int main() {
    scanf("%d", &T);
    while (T--) {
        kase++;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &p[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int k = 1; k <= n; ++k)
                ans = max(ans, v[i] - k * abs(p[i]) + dp(i, i, k - 1, 0));
        printf("%d\n", ans);
    }
}