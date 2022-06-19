//采用递归和记忆化搜索，因为避免查找了很多不必要的状态，速度快了很多很多。
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100;
const double INF = 1 << 30;
const double eps = 1e-9;
double d[maxn][maxn];
int n, vis[maxn][maxn];
struct Point {
	double x, y;
} p[maxn];

double area (Point a, Point b, Point c) { //计算面积
	return fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) / 2;
}

bool judge (int a, int b, int c) { //判断合法性
	double cur = area(p[a], p[b], p[c]);
	for (int i = 0; i < n; i++) {
		if (i == a || i == b || i == c) continue;
		double tmp = area(p[a], p[b], p[i]) + area(p[b], p[c], p[i]) + area(p[c], p[a], p[i]);
		if (fabs(tmp - cur) < eps) return false;
	}
	return true;
}

double dp(int i, int j) {
	if (vis[i][j]) return d[i][j];
	vis[i][j] = 1;
	d[i][j] = INF;
	if (i == j || i + 1 == j) return d[i][j] = 0;
	for (int k = i + 1; k < j; ++k)
		if (judge(i, j, k))
			d[i][j] = min(d[i][j], max(max(dp(i, k), dp(k, j)), area(p[i], p[j], p[k])));
	return d[i][j];
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
		memset(vis, 0, sizeof(vis));
		printf("%.1lf\n", dp(0, n - 1));
	}
	return 0;
}