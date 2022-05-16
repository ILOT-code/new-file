#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
const double INF = 1e30;
int kase, n, vis[maxn][maxn][2], pos;
double d[maxn][maxn][2], x, v, sumd[maxn];
struct Point {
	double x, c, dt;
	bool operator<(const Point &rhs) const {
		return x < rhs.x;
	}
} p[maxn];

double cost(int i, int j, double x1, double x2) {
	double t = fabs(x2 - x1) / v;
	double cur = sumd[n] - (sumd[j] - sumd[i] + p[i].dt);
	return t * cur;
}
double dp(int i, int j, int f) {
	if (vis[i][j][f] == kase) return d[i][j][f];
	vis[i][j][f] = kase;
	double &ans = d[i][j][f];
	ans = INF;
	if (i == 0 && j == n) return ans = 0;
	double x = (f == 0 ? p[i].x : p[j].x);
	if (i > 0) ans = min(ans, dp(i - 1, j, 0) + cost(i, j, x, p[i - 1].x));
	if (j < n) ans = min(ans, dp(i, j + 1, 1) + cost(i, j, x, p[j + 1].x));
	return ans;
}

int main() {
	memset(vis, 0, sizeof(vis));
	while (~scanf("%d%lf%lf", &n, &v, &x) && n) {
		kase++;
		double sumc = 0;
		pos = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lf%lf%lf", &p[i].x, &p[i].c, &p[i].dt);
			sumc += p[i].c;
			if (p[i].x < x) pos++;
		}
		p[0].x = x; p[0].c = 0; p[0].dt = 0;
		sort(p, p + n + 1);
		sumd[0] = p[0].dt;
		for (int i = 1; i <= n; ++i) sumd[i] = sumd[i - 1] + p[i].dt;
		printf("%.0lf\n", floor(dp(pos, pos, 0) + sumc));
	}
	return 0;
}

