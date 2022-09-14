#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
    int from, to, dist;
    Edge(int u, int v, int w): from(u), to(v), dist(w) {}
};

struct Bellman_Ford {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn], cnt[maxn], d[maxn];

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; ++i) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int dist) {
        edges.push_back(Edge(from, to, dist));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    bool bellman_ford(int s) {
        queue<int> Q;
        for (int i = 0; i < n; ++i) inq[i] = 0, cnt[i] = 0, d[i] = INF;
        d[s] = 0; inq[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for (int i = 0; i < G[u].size(); ++i) {
                Edge& e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.dist) {
                    d[e.to] = d[u] + e.dist;
                    cnt[e.to] = cnt[u] + 1;
                    if (cnt[e.to] >= n) return false;
                    if (!inq[e.to]) Q.push(e.to), inq[e.to] = true;
                }
            }
        }
        return true;
    }
};
Bellman_Ford g;

int main() {
    int n, kase = 0;
    while (~scanf("%d", &n) && n != -1) {
        g.init(2 * n + 1);
        char ch[maxn];
        for (int i = 1; i <= n; ++i) {
            scanf("%s", ch + 1);
            for (int j = 1; j <= n; ++j) {
                if (ch[j] == '0') {
                    g.AddEdge(j + n, i, 0);
                    g.AddEdge(i, j + n, 0);
                }
                else if (ch[j] == '+') g.AddEdge(i, j + n, -1);
                else if (ch[j] == '-') g.AddEdge(j + n, i, -1);
            }
        }
        for (int i = 1; i <= 2 * n; ++i) g.AddEdge(0, i, 0);

        printf("Case %d: ", ++kase);
        if (g.bellman_ford(0)) {
            sort(g.d + 1, g.d + 1 + 2 * n);
            int ans = 0;
            for (int i = 1; i <= 2 * n; ++i) ans += abs(g.d[i] - g.d[n]);
            printf("%d\n", ans);
        }
        else printf("-1\n");
    }
    return 0;
}
