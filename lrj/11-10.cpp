#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 200 + 10;
const int INF = 0x3f3f3f3f;

struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int c, int f, int w): from(u), to(v), cap(c), flow(f), cost(w) {}
};

struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];
  int d[maxn];
  int p[maxn];
  int a[maxn];

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BellmanFord(int s, int t, int& flow, int& cost) {
    for (int i = 0; i < n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if (!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
        }
      }
    }
    if (d[t] == INF) return false;
    flow += a[t];
    cost += d[t] * a[t];
    for (int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u] ^ 1].flow -= a[t];
    }
    return true;
  }

  // 需要保证初始网络中没有负权圈
  int MincostMaxflow(int s, int t, int& cost) {
    int flow = 0; cost = 0;
    while (BellmanFord(s, t, flow, cost));
    return flow;
  }

};
MCMF g;

int main() {
  int n;
  while (~scanf("%d", &n) && n) {
    g.init(n * 2 + 2);
    for (int i = 1; i <= n; ++i) {
      g.AddEdge(0, i, 1, 0);
      g.AddEdge(n + i, n * 2 + 1, 1, 0);
    }
    for (int i = 1, t, d; i <= n; ++i) {
      while (~scanf("%d", &t) && t) {
        scanf("%d", &d);
        g.AddEdge(i, t + n, 1, d);
      }
    }
    int cost;
    int flow = g.MincostMaxflow(0, n * 2 + 1, cost);
    if (flow < n) printf("N\n");
    else printf("%d\n", cost);
  }
  return 0;
}
