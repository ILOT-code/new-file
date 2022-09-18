#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#define bll __int128
using namespace std;

const int maxn = 80 + 5;
bll f[maxn][maxn], power[maxn];
bool vis[maxn][maxn];
int n, m, g[maxn];

void init() {
    power[0] = 1;
    for (int i = 1; i < maxn; ++i) power[i] = power[i - 1] * 2;
}
void print(bll x) {
    if (!x) return;
    if (x) print(x / 10);
    putchar(x % 10 + '0');
}
bll dp(int l, int r) {
    if (vis[l][r]) return f[l][r];
    vis[l][r] = 1;
    if (l == r) return f[l][r] = g[l] * power[m];
    bll t1 = dp(l + 1, r) + power[m - r + l] * g[l];
    bll t2 = dp(l, r - 1) + power[m - r + l] * g[r];
    return f[l][r] = max(t1, t2);
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    bll ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) scanf("%d", &g[j]);
        memset(vis, 0, sizeof(vis));
        ans += dp(1, m);
    }
    if (!ans) printf("0");
    else print(ans);
    return 0;
}