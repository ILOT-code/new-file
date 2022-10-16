#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 8e4 + 10;
const int maxm = 2e5 + 10;
int n, m, t, T, cnt, tot, s, ans;
int head[maxn], dfn[maxn], low[maxn];
int col[maxn], H[maxn], sum[maxn], dis[maxn], V[maxn];
struct Edge {
    int from, to, next, val, k;
    Edge(int from = 0, int to = 0, int next = 0, int val = 0, int k = 0): from(from), to(to), next(next), val(val), k(k) {}
} e[maxm], E[maxm];
stack<int> st;
queue<int> q;

void AddEdge(int u, int v, int w, int k) {
    e[++t] = Edge(u, v, head[u], w, k);
    head[u] = t;
}
void Add(int u, int v, int w) {
    E[++T] = Edge(u, v, H[u], w);
    H[u] = T;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (col[v]) continue;
        if (!dfn[v]) tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) {
        tot++;
        int v;
        do {
            v = st.top();
            st.pop();
            col[v] = tot;
        } while (v != u);
    }
}

void spfa(int s) {
    memset(dis, -1, sizeof(dis));
    memset(V, 0, sizeof(V));
    dis[s] = sum[s]; V[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        V[u] = 0;
        for (int i = H[u]; i; i = E[i].next) {
            int v = E[i].to, w = E[i].val;
            if (dis[v] < dis[u] + w + sum[v]) {
                dis[v] = dis[u] + w + sum[v];
                if (!V[v]) { V[v] = 1; q.push(v); }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        double k;
        scanf("%d%d%d%lf", &x, &y, &z, &k);
        AddEdge(x, y, z, k * 10);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; ++i) {
        int x = e[i].from, y = e[i].to, z = e[i].val, k = e[i].k;
        if (col[x] == col[y])
            while (z) {
                sum[col[x]] += z;
                z = z * k / 10;
            }
        else Add(col[x], col[y], z);
    }
    scanf("%d", &s); s = col[s];
    spfa(s);
    for (int i = 1; i <= tot; i++) ans = max(ans, dis[i]);
    printf("%d\n", ans);
    return 0;
}