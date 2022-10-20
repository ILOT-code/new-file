#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int mod = 100000000;
int m, n, gra[13], st[1500], cnt;
int d[13][1500];

void init() {
	for (int i = 0; i < 1 << n; ++i) {
		if (i & (i << 1))continue;
		st[++cnt] = i;
	}
}
bool check(int i, int j) {
	return gra[i] == (gra[i] | st[j]);
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i)
		for (int j = 1, t; j <= n; ++j) {
			scanf("%d", &t);
			if (t) gra[i] |= 1 << (j - 1);
		}

	init();
	d[0][1] = 1;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= cnt; ++j)if (check(i, j))
				for (int k = 1; k <= cnt; ++k, d[i][j] %= mod) if (!(st[j] & st[k]))
						d[i][j] += d[i - 1][k];

	int ans = 0;
	for (int i = 1; i <= cnt; ++i, ans %= mod) ans += d[m][i];
	printf("%d\n", ans);
	return 0;
}