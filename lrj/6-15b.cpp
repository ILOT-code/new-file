#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100;
int G[maxn][maxn], vis[maxn], topo[maxn];
int t, n, m;
bool dfs(int u) {
    vis[u] = -1;
    for (int v = 0; v < n; ++v)
        if (G[u][v])
            if (vis[v] == -1 || (!vis[v] && !dfs(v))) return false;
    vis[u] = 1;
    topo[t--] = u;
    return true;
}
bool toposort() {
    t = n - 1;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i)
        if (!vis[i] && !dfs(i)) return false;
    return true;
}
int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        memset(G, 0, sizeof(G));
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u][v] = 1;
        }
        if (toposort())
            for (int i = 0; i < n; ++i)
                printf("%d ", topo[i]);
        else printf("wrong");
    }
    return 0;
}