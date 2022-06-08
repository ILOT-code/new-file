//任意一个m边形，它如果存在，从0点开始，向两边延伸，直到到达这个多边形的端点，设为i，j;
//则它的所有点都在i,j的范围内，所以不用考虑环。
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn  = 40 + 5;
const double PI = acos(-1.0);
int n, m;
double p[maxn], dist[maxn][maxn], area[maxn][maxn][maxn], dp[maxn][maxn][maxn];

double distan(double p1, double p2) {
	double a = fabs(p2 - p1);
	if (a > 0.5) a = 1 - a;
	return 2 * sin(a * PI);
}
double calarea(double a, double b, double c) {
	double x = (a + b + c) / 2;
	return sqrt(x * (x - a) * (x - b) * (x - c));
}

double solve() {
	memset(dp, 0, sizeof dp);
	for (int len = 3; len <= m; ++len)
		for (int i = 0; i < n; ++i)
			for (int j = i + len - 1; j < n; ++j)
				for (int x = i + len - 2; x < j; ++x)
					dp[i][j][len] = max(dp[i][j][len], dp[i][x][len - 1] + area[i][x][j]);
	double ans = 0.0;
	for (int i = 0; i < n; ++i)
		for (int j = i + m - 1; j < n; ++j) ans = max(ans, dp[i][j][m]);
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		for (int i = 0; i < n; ++i) scanf("%lf", &p[i]);
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) dist[i][j] = dist[j][i] = distan(p[i], p[j]);
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				for (int k = j + 1; k < n; ++k)
					area[i][j][k] = calarea(dist[i][j], dist[j][k], dist[i][k]);
		printf("%.6lf\n", solve());
	}
	return 0;
}