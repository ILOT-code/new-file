#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using namespace std;
const int maxn = 1000000 + 10;
struct node {
    int left, right, face;
} q[maxn];
int vis[maxn], layer[maxn];
void del(int id) {
    vis[id] = 1;
    q[q[id].left].right = q[id].right;
    q[q[id].right].left = q[id].left;
}
int main()
{
    int kase, t = 0;
    scanf("%d", &kase);
    int n, m;
    while (kase--) {
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof(vis));
        memset(layer, 0, sizeof(layer));
        for (int i = 0; i < n; i++) {
            q[i].left = i - 1;
            q[i].right = i + 1;
        }
        q[0].left = n - 1;
        q[n - 1].right = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            q[u].face = v;
            q[v].face = u;
            layer[u] = 1;
            layer[v] = -1;
        }
        for (int i = 0; i < n; i++)if (layer[i] == 0) del(i);
        int k = 0, count = 2 * m, u, v;
        while (count) {
            int ok = 1;
            while (vis[k]) k++;
            for (int i = q[k].right; ok && i != k; i = q[i].right) {
                u = i; v = q[i].right;
                if (layer[u] == layer[v] && (q[q[u].face].right == q[v].face || q[q[v].face].right == q[u].face)) {
                    del(u); del(q[u].face); del(v); del(q[v].face);
                    count -= 4;
                    ok = 0;
                }
                else if (q[u].face == v) {
                    del(u); del(v);
                    count -= 2;
                    ok = 0;
                }
            }
            if (ok) break;
        }
        printf("Case #%d: ", ++t);
        if (count) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}