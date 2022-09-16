#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
const int mod = 1e6 + 7;
int n, m, d[maxn][maxn];

int main() {
	scanf("%d%d", &n, &m);
	d[0][0] = 1;
	for (int i = 1, a; i <= n; ++i) {
		scanf("%d", &a);
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= min(a, j); ++k)
				d[i][j] = (d[i][j] + d[i - 1][j - k]) % mod;
	}
	printf("%d\n", d[n][m]);
	return 0;
}

