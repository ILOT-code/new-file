#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
double x[maxn], y[maxn], dist[maxn][maxn], d[maxn][maxn];

int main() {
	int n;
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i)
			scanf("%lf%lf", &x[i], &y[i]);
		for (int i = n - 1; i >= 0; --i)
			for (int j = 0; j < i; ++j )
				dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		for (int i = n - 2; i >= 1; --i)
			for (int j = 0; j < i; ++j)
				if (i == n - 2) d[i][j] = dist[n - 1][i] + dist[n - 1][j];
				else d[i][j] = min(	d[i + 1][j] + dist[i + 1][i], d[i + 1][i] + dist[i + 1][j]);
		printf("%.2lf\n", dist[1][0] + d[1][0]);
	}
	return 0;
}