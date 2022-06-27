//若gcd(a,b)!=1,a',b'一定包含在合法的边长为a,b的长方形里面，则一定重复。
//gcd(a,b)=gcd(c,d)=1,b/a!=d/c那么它们一定不会重复。
//则只能和自己重复。gcd(a,b)=1,则边长为1,b的长方形,对角线上一定没有其它的点。就有了下面的程序。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 300 + 5;
int n, m, g[maxn][maxn];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	for (int i = 1; i < maxn; ++i)
		for (int j = 1; j < maxn; ++j)
			g[i][j] = gcd(i, j);

	while (~scanf("%d%d", &n, &m) && n) {
		int ans = 0;
		for (int x = 1; x <= m; ++x)
			for (int y = 1; y <= n; ++y)if (g[x][y] == 1) {
					int c = max(0, m - 2 * x) * max(0, n - 2 * y);
					ans += (m - x) * (n - y) - c;
				}
		printf("%d\n", 2 * ans);
	}
	return 0;
}
