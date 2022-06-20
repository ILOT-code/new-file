#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20 + 5;
int n, r, buy[maxn];
double p[maxn], sum[maxn];

void dfs(int d, int c, double prob) {
	if (c > r || d - c > n - r) return;
	if (d == n) {
		sum[n] += prob;
		for (int i = 0; i < n; ++i)
			if (buy[i] == 1) sum[i] += prob;
		return;
	}
	buy[d] = 0; dfs(d + 1, c, prob * (1 - p[d]));
	buy[d] = 1; dfs(d + 1, c + 1, prob * p[d]);
}

int main() {
	int kase = 0;
	while (~scanf("%d%d", &n, &r) && n) {
		for (int i = 0; i < n; ++i) scanf("%lf", &p[i]);
		memset(sum, 0, sizeof(sum));
		dfs(0, 0, 1.0);
		printf("Case %d:\n", ++kase);
		for (int i = 0; i < n; ++i)
			printf("%.6lf\n", sum[i] / sum[n]);
	}
	return 0;
}