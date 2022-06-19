#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxm = 11;
int kase, n, m, vis[1 << maxm][1 << maxm], d[1 << maxm][1 << maxm], cnt[1 << maxm][1 << maxm];

int dp(int s, int a) {
    if (cnt[s][a] == 1) return 0;
    int& ans = d[s][a];
    if (vis[s][a] == kase) return ans;
    vis[s][a] = kase;
    ans = m;
    for (int k = 0; k < m; k++)
        if (!(s & (1 << k))) {
            int s2 = s | (1 << k), a2 = a | (1 << k);
            if (cnt[s2][a2] >= 1 && cnt[s2][a] >= 1)  //如果cnt[s2][s2] > 0 而cnt[s2][a] = 0, 意味着在当前s,a下,k没有意义。
                ans = min(ans, max(dp(s2, a2), dp(s2, a)) + 1);
        }
    return ans;
}

int main() {
    char s[maxm + 10];
    memset(vis, 0, sizeof(vis)); //实际上可以用循环来初始化，使得计算量由O(n^4)降为O(n^3)。
    while (~scanf("%d%d", &m, &n)  && n) {
        ++kase;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0, stc = 0; i < n; ++i) {
            scanf("%s", s);
            stc = 0;
            for (int j = 0; j < m; ++j)if (s[j] == '1') stc |= (1 << j);
            for (int j = 0; j < 1 << m; ++j) cnt[j][j & stc]++;
        }
        printf("%d\n", dp(0, 0));
    }
    return 0;
}
