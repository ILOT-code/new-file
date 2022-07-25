#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using namespace std;

const int maxn = 20;
long long d[maxn + 1][maxn + 1][maxn + 1];

void init() {
    d[1][1][1] = 1;
    for (int i = 2; i <= maxn; ++i)
        for (int j = 1; j <= i; ++j)
            for (int k = 1; k <= i - j + 1; ++k)
                d[i][j][k] = d[i - 1][j][k] * (i - 2) + d[i - 1][j - 1][k] + d[i - 1][j][k - 1];
}
int main() {
    init();
    int T, n, L, R;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &L, &R);
        printf("%lld\n", d[n][L][R]);
    }
    return 0;
}
