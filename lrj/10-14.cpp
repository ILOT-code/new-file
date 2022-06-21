#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000;
const int mod = 10056;
int C[maxn + 1][maxn + 1], f[maxn + 1];

void init() {
    for (int i = 0; i <= maxn; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }

    f[0] = 1;
    for (int i = 1; i <= maxn; i++) {
        f[i] = 0;
        for (int j = 1; j <= i; j++) f[i] = (f[i] + C[i][j] * f[i - j]) % mod;
    }
}

int main() {
    init();
    int T, n, kase = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("Case %d: %d\n", ++kase, f[n]);
    }
    return 0;
}
