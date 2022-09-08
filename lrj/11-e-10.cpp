/**证明 check(mid) is true 等价于 存在使得边界上最小点为mid的操作存在。
 * 正推：在新图中，一入点u，与对应出边u'.如果s->u的流量为f，且f<army[u],则army[i]-f的兵留在原地。
 * u->u'的流量f',则又有f’的兵留下来，u-v'的流量代表着前往v的兵。
 * 那些边界点可能一开始就有兵留下来（源点处未满载），则边界点兵至少为mid。
 * 则就在原图中构造了一些操作，存在使得边界上最小点至少为mid。
 * 反推：原图存在操作，使得边界上最小点为mid.对于一个边界点u，兵为c,c>mid.
 * 那么，只需把对应图中s->u,或v->u'上有兵运送的点给减少流量，那么就能使谓词check(mid)为真。
 * 下面证明这个二分法是有效的。
 * 这种构图的意义就是把点尽量向边界点运送。如果check(mid)为真。
 * 则对于一个c,c<mid.在check(mid)的那个图中，采取与反推中类似的办法，使得某些边减少流量，就得到check(c)为真。
 * 则二分法成立。
   */
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 2 * 100 + 5;
int T, n, army[maxn];
bool link[maxn][maxn];

struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
    };
    int s, t;
    vector <Edge> edges;
    vector <int> G[2 * maxn];

    void init(int n) {
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    inline void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0 , 0));
        int top = edges.size();
        G[from].push_back(top - 2);
        G[ to ].push_back(top - 1);
    }

    bool vis[maxn];
    int d[maxn], cur[maxn];
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue <int> Q;
        Q.push(s); d[s] = 0; vis[s] = 1;
        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (vis[e.to] || e.cap <= e.flow)continue;
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                Q.push(e.to);
            }
        }
        return vis[t];
    }
    int DFS(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 != d[e.to])continue;
            if ((f = DFS(e.to, min(a, e.cap - e.flow))) <= 0)continue;
            e.flow += f;
            edges[G[x][i] ^ 1].flow -= f;
            flow += f; a -= f;
            if (a == 0) break;
        }
        return flow;
    }
    int maxFlow(int s, int t) {
        this->s = s; this->t = t;
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF) ;
        }
        return flow;
    }
} g;

bool check(int mid) {
    int s = 0, t = 2 * n + 2;
    g.init(t);
    int sum = 0;
    for (int i = 1; i <= n; ++i)if (army[i]) {
            bool boder = 0;
            g.AddEdge(s, i , army[i]);
            g.AddEdge(i, n + i, army[i]);
            for (int j = 1; j <= n; ++j)if (link[i][j]) {
                    if (army[j]) g.AddEdge(i, j + n, INF);
                    else boder = 1;
                }
            if (boder) {sum += mid; g.AddEdge(i + n, t, mid);}
            else { sum++; g.AddEdge(i + n, t, 1 ); }
        }
    return sum == g.maxFlow(s, t);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int L = 0, R = 1, ans = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", &army[i]), R += army[i];
        getchar();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                char ch;
                scanf("%c", &ch);
                link[i][j] = (ch == 'Y');
            }
            getchar();
        }
        while (L < R) {
            int mid = (L + R) >> 1 ;
            if (check(mid)) {
                ans  = mid ;
                L = mid + 1;
            } else R = mid;
        }
        printf("%d\n", ans);
    }
    return 0;
}
