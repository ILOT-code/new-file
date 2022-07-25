#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10005;
int vis[maxn + 1], p[maxn + 1], pn, n, f[maxn + 1], fn, ans;

void init() {
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) p[pn++] = i;
        for (int j = 0; j < pn && i * p[j] < maxn; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}

void build(int n) {
    fn = 0;
    ans = 200000000;
    for (int i = 0; i < pn && (p[i] - 1) * (p[i] - 1) <= n; ++i)
        if (n % (p[i] - 1) == 0) f[fn++] = p[i];
}

bool judge(int sum) {
    for (int i = 0; i < pn && p[i] * p[i] <= sum; ++i)
        if (sum % p[i] == 0) return false;
    if (sum <= f[fn - 1]) return false;
    return true;
}

void dfs(int now, int sum, int tot) {
    if (now == fn) {
        if (sum == 1) ans = min(ans, tot);
        else if (judge(sum + 1)) {
            tot *= (sum + 1);
            ans = min(ans, tot);
        }
        return;
    }
    dfs(now + 1, sum, tot);
    if (sum % (f[now] - 1)) return;
    sum /= (f[now] - 1);
    tot *= f[now];
    dfs(now + 1, sum, tot);
    while (sum % f[now] == 0) {
        sum /= f[now];
        tot *= f[now];
        dfs(now + 1, sum, tot);
    }
}

int main() {
    init();
    int kase = 0;
    while (~scanf("%d", &n) && n) {
        build(n);
        dfs(0, n, 1);
        printf("Case %d: %d %d\n", ++kase, n, ans);
    }
    return 0;
}