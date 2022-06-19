//accepted
//注意输出格式 不能多一个空格
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 100000 + 5;
const int INF = 1000000000;
struct Edge {
    int u, v, c;
    Edge(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {};
};
vector<Edge> edges;
vector<int> G[maxn];
vector<int> ans;
int n, d[maxn], vis[maxn];
void rev_bfs() {
    memset(vis, 0, sizeof(vis));
    d[n - 1] = 0;
    vis[n - 1] = 1;
    queue<int> q;
    q.push(n - 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < G[u].size(); ++i) {
            int idx = G[u][i];
            int v = edges[idx].v;
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
                d[v] = d[u] + 1;
            }
        }
    }
}
void bfs() {
    memset(vis, 0, sizeof(vis));
    vector<int> next;
    ans.clear();
    vis[0] = 1;
    next.push_back(0);
    for (int i = 0; i < d[0]; ++i) {
        int min_color = INF;
        for (int j = 0; j < next.size(); ++j) {
            int u = next[j];
            for (int k = 0; k < G[u].size(); ++k) {
                int idx = G[u][k];
                int v = edges[idx].v;
                if (d[v] + 1 == d[u])
                    min_color = min(min_color, edges[idx].c);
            }
        }
        ans.push_back(min_color);
        vector<int> next2;
        for (int j = 0; j < next.size(); ++j) {
            int u = next[j];
            for (int k = 0; k < G[u].size(); ++k) {
                int idx = G[u][k];
                int v = edges[idx].v;
                int c = edges[idx].c;
                if (d[u] == d[v] + 1 && !vis[v] && c == min_color) {
                    vis[v] = true;
                    next2.push_back(v);
                }
            }
        }
        next = next2;
    }
    printf("%d\n", ans.size());
    printf("%d", ans[0]);
    for (int i = 1; i < ans.size(); i++) printf(" %d", ans[i]);
    printf("\n");
}
void clean() {
    edges.clear();
    for (int i = 0; i < n; ++i)
        G[i].clear();
}
void addedge(int u, int v, int c) {
    edges.push_back(Edge(u, v, c));
    int ix = edges.size() - 1;
    G[u].push_back(ix);
}
int main() {
    int  m, u, v, c;
    while (scanf("%d%d", &n, &m) == 2) {
        clean();
        while (m--) {
            scanf("%d%d%d", &u, &v, &c);
            addedge(u - 1, v - 1, c);
            addedge(v - 1, u - 1, c);
        }
        rev_bfs();
        bfs();
    }
    return 0;
}
