#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000000 + 5;
unsigned long long seed;
int T, kase, n;
long double a[maxn], m, s;

long double gen() {
    static const long double Z = (long double)1.0 / (1LL << 32);
    seed >>= 16;
    seed &= ( 1ULL << 32 ) - 1;
    seed *= seed;
    return seed * Z;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%llu", &n, &seed);
        m = 0.0, s = 0.0;
        for (int i = 1; i <= n; i++)
            a[i] = gen(), m += a[i];
        m /= n;
        for (int i = 1; i <= n; i++)
            s += (a[i] - m) * (a[i] - m);
        printf("Case #%d: %.5Lf\n", ++kase, (long double)sqrt(s / n));
    }
    return 0;
}