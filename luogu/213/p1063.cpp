#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2 * 100 + 5;
int n, a[maxn], d[maxn][maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), a[n + i] = a[i];
	a[2 * n + 1] = a[1];
	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= 2 * n; ++i) {
			int j = i + len;
			for (int k = i; k < j; ++k)
				d[i][j] = max(d[i][j], d[i][k] + d[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
		}
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans = max(ans, d[i][i + n - 1]);
	printf("%d\n", ans);
	return 0;
}