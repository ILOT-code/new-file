#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define fi first
#define se second
typedef pair<double, double> PDD;

const int maxn = 15;
int n;
double d[1 << maxn][maxn], l[maxn][maxn];
PDD p[maxn];

double cal(int i, int j) {return sqrt((p[i].fi - p[j].fi) * (p[i].fi - p[j].fi) + (p[i].se - p[j].se) * (p[i].se - p[j].se));}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].fi, &p[i].se);
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j) l[i][j] = l[j][i] = cal(i, j);
	memset(d, 0x7f, sizeof(d));
	double ans = d[0][0];
	for (int i = 0; i < n; ++i) d[1 << i][i] = sqrt(p[i].fi * p[i].fi + p[i].se * p[i].se);
	for (int s = 1; s < (1 << n); ++s) {
		for (int i = 0; i < n; ++i)if (s & (1 << i)) {
				for (int j = 0; j < n; ++j)if (!(s & (1 << j))) {
						int st = s | (1 << j);
						d[st][j] = min(d[st][j], d[s][i] + l[i][j]);
					}
			}
	}
	for (int i = 0; i < n; ++i) ans = min(ans, d[(1 << n) - 1][i]);
	printf("%.2lf\n", ans);
}