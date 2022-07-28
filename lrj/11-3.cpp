#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
const int maxq = 8;
int T, n, q, p[maxn];
int x[maxn], y[maxn], cost[maxq];
vector<int> subn[maxq];
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x; }

struct Edge {
    int u, v, d;
    Edge(int u, int v, int d): u(u), v(v), d(d) {}
    bool operator < (const Edge& rhs) const { return d < rhs.d; }
};

int MST(int cnt, const vector<Edge>& e, vector<Edge>& used) {
    int m = e.size(), ans = 0;
    for (int i = 0; i < m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u != v) {
            p[u] = v;
            ans += e[i].d;
            used.push_back(e[i]);
            if (--cnt == 0) break;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        for (int i = 0, cnt; i < q; ++i) {
            scanf("%d%d", &cnt, &cost[i]);
            subn[i].clear();
            for (int j = 0, q; j < cnt; ++j) {
                scanf("%d", &q);
                subn[i].push_back(q - 1);
            }
        }
        for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
        vector<Edge> e, need;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                int c = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                e.push_back(Edge(i, j, c));
            }
        for (int i = 0; i < n; ++i) p[i] = i;
        sort(e.begin(), e.end());
        int ans = MST(n, e, need);

        for (int mask = 0; mask < (1 << q); ++mask) {
            for (int i = 0; i < n; ++i) p[i] = i;
            int cnt = n - 1, c = 0;
            for (int i = 0; i < q; ++i) if (mask & (1 << i)) {
                    c += cost[i];
                    for (int j = 1; j < subn[i].size(); ++j) {
                        int u = find(subn[i][j]), v = find(subn[i][0]);
                        if (u != v) {p[u] = v; cnt--;}
                    }
                }
            vector<Edge> dummy;
            ans = min(ans, c + MST(cnt, need, dummy));
        }
        printf("%d\n", ans);
        if (T) printf("\n");
    }
    return 0;
}