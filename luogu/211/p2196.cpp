#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20 + 5;
const int INF = 0x3f3f3f3f;

int n, g[maxn][maxn], f[maxn], w[maxn], pre[maxn];

void print(int x) {
	if (!x) return;
	print(pre[x]);
	printf("%d ", x);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]), f[i] = w[i];
	for (int i = 1; i < n; ++i)
		for (int j = i + 1; j <= n; ++j)
			scanf("%d", &g[i][j]);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j)
			if (g[j][i] && f[j] + w[i] > f[i]) {
				f[i] = f[j] + w[i];
				pre[i] = j;
			}

	int ans = 0, sta = 0;
	for (int i = 1; i <= n; ++i)
		if (f[i] > ans) {
			ans = f[i];
			sta = i;
		}

	print(sta);
	printf("\n%d\n", ans);
	return 0;
}