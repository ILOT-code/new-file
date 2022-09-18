#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 248 + 5;
int n, a[maxn], d[maxn][maxn];

int main() {
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), d[i][i] = a[i], ans = max(ans, a[i]);
	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= n; ++i) {
			int j = i + len;
			for (int k = i; k < j; ++k)
				if (d[i][k] != 0 && d[k + 1][j] != 0 && d[i][k] == d[k + 1][j]) {
					d[i][j] = d[i][k] + 1;
					ans = max(ans, d[i][j]);
					break;
				}
		}
	printf("%d\n", ans);
	return 0;
}