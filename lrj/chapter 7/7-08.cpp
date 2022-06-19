#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 200 + 5;
int vis[maxn][maxn], ans[maxn];
int cap[3];
struct Node {
    int v[3], dist;
    bool operator<(const Node &rhs) const {
        return  dist > rhs.dist;
    }
};
void update_ans(Node &u) {
    for (int i = 0; i < 3; ++i) {
        int d = u.v[i];
        if (ans[d] < 0 || u.dist < ans[d])    ans[d] = u.dist;
    }
}
void solve(int a, int b, int c, int d) {
    cap[0] = a; cap[1] = b; cap[2] = c;
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    priority_queue<Node> q;
    Node start;
    start.dist = 0;
    start.v[0] = start.v[1] = 0; start.v[2] = c;
    q.push(start);
    while (!q.empty()) {
        Node u = q.top(); q.pop();
        update_ans(u);
        if (ans[d] >= 0)  break;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (u.v[i] == 0 || u.v[j] == cap[j])   continue;
                Node v;
                memcpy(&v, &u, sizeof(u));
                int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
                v.dist += amount;
                v.v[i] -= amount;
                v.v[j] += amount;
                if (!vis[v.v[0]][v.v[1]]) {
                    vis[v.v[0]][v.v[1]] = 1;
                    q.push(v);
                }
            }
    }
    while (d >= 0) {
        if (ans[d] >= 0) {
            printf("%d %d\n", ans[d], d);
            return;
        }
        d--;
    }
}
int main() {
    int T, a, b, c, d;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0;
}