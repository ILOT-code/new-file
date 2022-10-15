#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;

vector<int>sons[maxn];
int n, m, vis[maxn], dp[maxn][maxn], val[maxn][maxn];

void dfs(int u) {
    vis[u] = 1;
    for (int i = 0; i < sons[u].size(); ++i) {
        int v = sons[u][i];
        if (vis[v]) continue;
        vis[v] = 1;
        dfs(v);
        for (int j = m; j >= 1; --j)
            for (int k = 0; k <= j - 1; ++k)
                dp[u][j] = max(dp[u][j], dp[u][j - k - 1] + dp[v][k] + val[u][v]);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        sons[u].push_back(v); sons[v].push_back(u);
        val[u][v] = val[v][u] = w;
    }
    dfs(1);
    printf("%d\n", dp[1][m]);
    return 0;
}