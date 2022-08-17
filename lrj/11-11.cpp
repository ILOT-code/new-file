#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 300 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
    int from, to, cost, open, close;
    Edge(int u, int v, int d, int a, int b): from(u), to(v), cost(d), open(a), close(b) {}
};
struct HeadNode {
    int d, u;
    HeadNode(int d, int u): d(d), u(u) {}
    bool operator<(const HeadNode& rhs) const {
        return d > rhs.d;
    }
};
struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool done[maxn];
    int d[maxn], p[maxn];
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cost, int open, int close) {
        edges.push_back(Edge(from, to, cost, open, close));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    void dijkstra(int s) {
        priority_queue<HeadNode> Q;
        for (int i = 0; i < n; ++i) d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push(HeadNode(0, s));
        while (!Q.empty()) {
            HeadNode x = Q.top(); Q.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0; i < G[u].size(); ++i) {
                Edge& e = edges[G[u][i]];
                if (e.cost > e.open) continue;
                int res = x.d, T = e.open + e.close, cur = x.d % T;
                if (cur + e.cost <= e.open) res += e.cost;
                else res += T - cur + e.cost;
                if (d[e.to] > res) {
                    d[e.to] = res;
                    Q.push(HeadNode(res, e.to));
                }
            }
        }
    }
};
Dijkstra g;

int main() {
    int n, m, s, t, kase = 0;
    while (~scanf("%d%d%d%d", &n, &m, &s, &t)) {
        g.init(n);
        for (int i = 0; i < m; ++i) {
            int u, v, a, b, t;
            scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
            g.AddEdge(u - 1, v - 1, t, a, b);
        }
        g.dijkstra(s - 1);
        printf("Case %d: %d\n", ++kase, g.d[t - 1]);
    }
    return 0;
}
