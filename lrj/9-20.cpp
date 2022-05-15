#include<cstdio>
using namespace std;

const int maxk = 100;
const int maxa = 63;
unsigned long long d[maxk + 1][maxa + 1];

int main() {
    for (int i = 1; i <= maxk; ++i)
        for (int j = 1; j <= maxa; ++j)
            d[i][j] = d[i - 1][j - 1] + 1 + d[i][j - 1];
    int k;
    long long n;
    while (~scanf("%d%lld", &k, &n) && k) {
        int ans = -1;
        for (int i = 1; i <= maxa; ++i)
            if (d[k][i] >= n) {ans = i; break;}
        if (ans < 0) printf("More than %d trials needed.\n", maxa);
        else printf("%d\n", ans);
    }
    return 0;
}
