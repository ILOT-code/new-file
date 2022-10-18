#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int n, k, cnt;
int st[100], num[100];
LL d[10][100][100];

void init() {
	for (int i = 0; i < 1 << n; ++i) {
		if ((i << 1)&i) continue;
		st[++cnt] = i;
		int t = i;
		for (int j = 0; j < n; ++j, t >>= 1) if (t & 1) num[cnt]++;
	}
}
void dp() {
	d[0][1][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= cnt; ++j)
			for (int c = num[j]; c <= k; ++c)
				for (int t = 1; t <= cnt; ++t)
					if (!(st[t]&st[j]) && !(st[t] & (st[j] << 1)) && !(st[t] & (st[j] >> 1)))
						d[i][j][c] += d[i - 1][t][c - num[j]];
	LL ans = 0;
	for (int i = 1; i <= cnt; ++i) ans += d[n][i][k];
	printf("%lld\n", ans);
}
int main() {
	scanf("%d%d", &n, &k);
	init();
	dp();
	return 0;
}