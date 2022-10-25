#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000 + 10;
int n, q, up[maxn][16], dn[maxn][16], Log[maxn];

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, t; i <= n; ++i) scanf("%d", &t), up[i][0] = dn[i][0] = t;
	Log[1] = 0; Log[2] = 1;
	for (int i = 3; i <= n; ++i) Log[i] = Log[i / 2] + 1;

	for (int j = 1; j <= Log[n]; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			up[i][j] = max(up[i][j - 1], up[i + (1 << (j - 1))][j - 1]);
			dn[i][j] = min(dn[i][j - 1], dn[i + (1 << (j - 1))][j - 1]);
		}
	for (int i = 0, a, b; i < q; ++i) {
		scanf("%d%d", &a, &b);
		int s = Log[b - a + 1];
		printf("%d\n", max(up[a][s], up[b - (1 << s) + 1][s]) - min(dn[a][s], dn[b - (1 << s) + 1][s]));
	}
	return 0;
}