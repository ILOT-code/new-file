#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);
const int maxn = 2000 + 10;
int n, kase, vis[maxn], ans[maxn];

bool dcmp(double a, double b) { return a - b < -eps;}
double rg(double a) {
    if (a > 2 * pi) a -= 2 * pi;
    return a;
}

int main() {
    vector<double> angs;
    while (~scanf("%d", &n) && n) {
        angs.clear();
        for (int i = 0; i <= n + 2; i++) ans[i] = vis[i] = 0;
        for (int i = 0; i < n; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            double ang = atan2(y, x);
            if (ang < 0) ang += 2 * pi;
            angs.push_back(ang);
        }
        sort(angs.begin(), angs.end());
        for (int k = 3; k <= n; k++)
            for (int i = 0; i < n; i++) {
                int pt = 1;
                if (vis[i] == k) continue;
                vis[i] = k;
                for (int p = 1; p < k; p++) {
                    auto ppr = equal_range(angs.begin(), angs.end(), rg(angs[i] + pi * 2 * p / k), dcmp);
                    if (ppr.first == ppr.second) break;
                    vis[ppr.first - angs.begin()] = k;
                    pt++;
                }
                if (pt == k) ans[k]++;
            }
        printf("Case %d:\n", ++kase);
        for (int k = 3; k <= n; k++)
            if (ans[k]) printf("%d %d\n", k, ans[k]);
    }
    return 0;
}