#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 128;
const int maxm = 11;
int kase, n, m, vis[1 << maxm][1 << maxm], d[1 << maxm][1 << maxm], cnt[1 << maxm][1 << maxm];
char objects[maxn][maxm + 100];

int dp(int s, int a) {
    if (cnt[s][a] == 1) return 0;
    int& ans = d[s][a];
    if (vis[s][a] == kase) return ans;
    vis[s][a] = kase;
    ans = m;
    for (int k = 0; k < m; k++)
        if (!(s & (1 << k))) {
            int s2 = s | (1 << k), a2 = a | (1 << k);
            if (cnt[s2][a2] >= 1 && cnt[s2][a] >= 1)  //如果cnt[s2][s2] > 0 而cnt[s2][a] < 0, 意味着在当前s,a下,k没有意义。
                ans = min(ans, max(dp(s2, a2), dp(s2, a)) + 1);
        }
    return ans;
}

void init() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        int features = 0;
        for (int f = 0; f < m; f++)
            if (objects[i][f] == '1') features |= (1 << f);
        for (int s = 0; s < (1 << m); s++)
            cnt[s][s & features]++;
    }
}

int main() {
    memset(vis, 0, sizeof(vis));
    while (scanf("%d%d", &m, &n) == 2 && n) {
        ++kase;
        for (int i = 0; i < n; i++) scanf("%s", objects[i]);
        init();
        printf("%d\n", dp(0, 0));
    }
    return 0;
}
