//采用递推
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 100;
const double INF = 1 << 30;
const double eps = 1e-9;
double d[maxn][maxn];
int n;
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

double dp() {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 2; ++j) d[i][(i + j) % n] = 0;
	for (int len = 3; len <= n; ++len)
		for (int i = 0; i + len - 1 < n; ++i) {
			int j = i + len - 1;
			d[i][j] = INF;
			for (int k = i + 1; k < j; ++k)
				if (judge(i, j, k))
					d[i][j] = min(d[i][j], max(max(d[i][k], d[k][j]), area(p[i], p[j], p[k])));
		}
	return d[0][n - 1];
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
		printf("%.1lf\n", dp());
	}
	return 0;
}