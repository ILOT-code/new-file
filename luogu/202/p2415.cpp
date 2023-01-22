#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define fi first
#define se second
typedef pair<int, long long> PIL;

const int maxn = 1000;
int a[maxn], n;

PIL solve(int l, int r) {
    int m = (l + r) / 2;
    if (l == r)
        return PIL(2, a[l]);
    PIL t1 = solve(l, m), t2 = solve(m + 1, r);
    return PIL(t1.fi * t2.fi, t1.fi * t2.se + t1.se * t2.fi);
}
int main() {
    while(~scanf("%d",&a[++n]));
    printf("%lld\n", solve(1, n-1).se);
    return 0;
}