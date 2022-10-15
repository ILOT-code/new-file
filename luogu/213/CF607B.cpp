#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;
const int INF = 0x3f3f3f3f;
int n, a[maxn], d[maxn][maxn];
int main() {
	scanf("%d", &n);
	memset(d, INF, sizeof(d));
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), d[i][i] = 1;
	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= n; ++i) {
			int j = i + len;
			if (a[i] == a[j]) d[i][j] = (len == 1 ? 1 : d[i + 1][j - 1]);
			for (int k = i; k < j; ++k) d[i][j] = min(d[i][j], d[i][k] + d[k + 1][j]);
		}
	printf("%d\n", d[1][n]);
	return 0;
}