#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2 * 100 + 5;
const int INF = 0x3f3f3f3f;
int n, a[maxn], sum[maxn], d[maxn][maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), a[n + i] = a[i];
	for (int i = 1; i <= 2 * n; ++i) sum[i] = sum[i - 1] + a[i];

	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= 2 * n; ++i) {
			int j = i + len;
			for (int k = i; k < j; ++k)
				d[i][j] = max(d[i][j], d[i][k] + d[k + 1][j] + sum[j] - sum[i - 1]);
		}

	int ans1 = 0;
	for (int i = 1; i <= n; ++i) ans1 = max(ans1, d[i][i + n - 1]);

	memset(d, INF, sizeof(d));
	for (int i = 1; i <= 2 * n; ++i) d[i][i] = 0;

	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= 2 * n; ++i) {
			int j = i + len;
			for (int k = i; k < j; ++k)
				d[i][j] = min(d[i][j], d[i][k] + d[k + 1][j] + sum[j] - sum[i - 1]);
		}
	int ans2 = INF;
	for (int i = 1; i <= n; ++i) ans2 = min(ans2, d[i][i + n - 1]);
	printf("%d\n%d\n", ans2, ans1);
}