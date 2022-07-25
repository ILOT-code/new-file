#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000010;
int n, vis[maxn], hp[maxn], hpnum, cnt[maxn];

void init() {
    for (int i = 5; i < 1010; i += 4)
        if (!vis[i])
            for (int j = i * i; j < maxn; j += i) vis[j] = 1;
    for (int i = 5; i < maxn; i += 4)
        if (!vis[i]) hp[hpnum++] = i;
    for (int i = 0; i < hpnum; ++i)
        for (int j = i; j < hpnum && 1LL * hp[i] * hp[j] < maxn; ++j)
            cnt[hp[i]*hp[j]] = 1;
    for (int i = 1; i < maxn; ++i) cnt[i] += cnt[i - 1];
}

int main() {
    init();
    while (~scanf("%d", &n) && n) printf("%d %d\n", n, cnt[n]);
    return 0;
}