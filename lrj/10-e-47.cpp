#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
const double eps = 1e-12;
long double g[maxn];

int main() {
    int r, n;
    while (scanf("%d%d", &r, &n) && !(r == 0 && n == 0)) {
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            g[i] = (long double)a / b;
        }
        long double dr = 1, up = 0;
        long double ans = 1.0, preans;
        do {
            dr *= r; up *= r;
            for (int i = 0; i < n; i++) {
                long long tmp = (long long)(g[i] * dr + eps);
                g[i] -= (long double)tmp / dr;
                up += tmp;
            }
            preans = ans;
            ans += (dr - up) / dr;
        } while (ans - preans > 1e-10);
        printf("%.6Lf\n", ans);
    }
    return 0;
}