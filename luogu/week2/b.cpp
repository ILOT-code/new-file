#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;

const int maxn = 5000 + 10;
const int INF = 0x3f3f3f3f;
int n, m, s, t ;
struct Edge {
    int from, to, cost;
    Edge(int u, int v, int d): from(u), to(v), cost(d) {}
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
    void AddEdge(int from, int to, int cost) {
        edges.push_back(Edge(from, to, cost));
        edges.push_back(Edge(to, from, cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    void dijkstra(int s) {
        priority_queue<PII, vector<PII>, greater<PII>> Q;
        for (int i = 0; i < n; ++i) d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push(PII(0, s));
        while (!Q.empty()) {
            PII head = Q.top(); Q.pop();
            int u = head.second;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0; i < G[u].size(); ++i) {
                Edge& e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = u;
                    Q.push(PII(d[e.to], e.to));
                }

            }
        }
    }
} g;

void print(int x) {
    if (x == s-1) {printf("%d", x+1); return;}
    print(g.p[x]); printf(" %d", x+1);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    g.init(n);
    for (int i = 0, u, v, c; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        g.AddEdge(u - 1, v - 1, c);
    }
    g.dijkstra(s - 1);
    printf("%d\n", g.d[t - 1]);
    print(t - 1);
    return 0;
}