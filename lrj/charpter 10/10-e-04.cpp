#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1299709 + 10;
int n, cnt = 0, p[maxn], vis[maxn], ans[maxn];
void init() {
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) {
            p[++cnt] = i;
            for (int j = p[cnt - 1] + 1; j < p[cnt]; ++j) ans[j] = p[cnt] - p[cnt - 1];
        }
        for (int j = 1; j <= cnt && i * p[j] < maxn; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}

int main() {
    init();
    while (scanf("%d", &n) && n) {
        printf("%d\n", ans[n]);
    }
    return 0;
}
