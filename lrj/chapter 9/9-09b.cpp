//改变了状态的定义方法,使可以运用四边形优化，复杂度为O(n^2)
#include<cstdio>
using namespace std;

const int maxn = 50 + 5;
const int INF = 1 << 30;
int n, L, a[maxn], m[maxn][maxn], d[maxn][maxn];

int main() {
	while (~scanf("%d%d", &L, &n) && L) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[n + 1] = L; a[0] = 0;
		for (int i = 1; i <= n + 1; ++i) {m[i][i] = i; d[i][i] = 0;}
		for (int len = 2; len <= n + 1; ++len)
			for (int i = 1; i + len - 1 <= n + 1; ++i) {
				int j = i + len - 1;
				d[i][j] = INF;
				for (int k = m[i][j - 1]; k <= m[i + 1][j]; ++ k) if (k < j)
						if (d[i][k] + d[k + 1][j] + a[j] - a[i - 1] < d[i][j]) {
							d[i][j] = d[i][k] + d[k + 1][j] + a[j] - a[i - 1];
							m[i][j] = k;
						}
			}
		printf("The minimum cutting is %d.\n", d[1][n + 1]);
	}
	return 0;
}