#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
LL solve(LL x, LL y, LL N, LL S, LL W, LL E) {
    LL res = 0;
    if ( S > N ) swap(S, N);
    if ( E > W ) swap(E, W);
    if (N) {
        res += x * y;
        y--;
        N -= S;
        if (N) {
            res += x * y * S * 2;
            N--;
        } else res += x * y * ( S * 2 - 1);
        S = 0;
    }
    if (W) {
        W -= E;
        if (W) {
            E *= 2;
            W--;
        } else E = E * 2 - 1;
        while ( (1 - x)*E >= x - y && N) { // xy + y(x-1)E + y(x-1) <= xy + x(y-1) + (x-1)(y-1)E
            res += x * y;
            N--; y--;
        }
        res += x * y; x--;
        res += x * y * E; E = 0;
    }
    while ( x * y > 0 && ( N + W) > 0) {
        res += x * y;
        if ( (y > x && N) || !W) {
            N--;
            y--;
        } else {
            W--;
            x--;
        }
    }
    return res;
}
int main() {
    int t = 1;
    LL y, x;
    while ( scanf("%lld%lld", &y, &x) && x && y) {
        LL N, S, W, E;
        scanf("%lld%lld%lld%lld", &N, &S, &W, &E);
        LL res = max(solve(x, y, N, S, W, E), solve(y, x, E, W, N, S));
        printf("Case %d: %lld\n", t++, res);
    }
}