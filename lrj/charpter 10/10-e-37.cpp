#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 10000 + 5;
int kase, n, m, dig[15];
int val[maxn], pre[maxn];

void print_ans(int x) {
    if (pre[x]) print_ans(pre[x]);
    printf("%d", val[x]);
}
void solve() {
    queue<int> q;
    for (int i = 1; i < 10; ++i)if (!dig[i]) {
            int mod = i % n;
            if (i >= n && mod == 0) {printf("%d\n", i); return;}
            if (pre[mod] != -1) continue;
            pre[mod] = 0; val[mod] = i; q.push(mod);
        }

    while (!q.empty()) {
        int mod = q.front(); q.pop();
        for (int i = 0; i < 10; ++i)if (!dig[i]) {
                int nmod = (10 * mod + i) % n;
                if (nmod == 0) {
                    print_ans(mod); printf("%d\n", i);
                    return;
                }
                if (pre[nmod] != -1) continue;
                pre[nmod] = mod; val[nmod] = i; q.push(nmod);
            }
    }
    puts("-1");
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(dig, 0, sizeof(dig));
        memset(pre, -1, sizeof(pre));
        for (int i = 0, t; i < m; ++i) {scanf("%d", &t); dig[t] = 1;}
        printf("Case %d: ", ++kase);
        solve();
    }
    return 0;
}