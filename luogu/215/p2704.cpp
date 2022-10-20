#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m, map[105], st[65], num[65], cnt;
int d[105][65][65];
void init() {
	for (int i = 0; i < 1 << m; ++i) {
		if (i & (i << 1) || i & (i << 2) || i & (i >> 1) || i & (i >> 2)) continue;
		st[++cnt] = i;
		int t = i;
		for (int j = 0; j < m; ++j, t >>= 1) if (t & 1) num[cnt]++;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			char c; cin >> c;
			if (c == 'H') map[i] |= (1 << (m - j));
		}
	init();
	for (int i = 1; i <= cnt; ++i) d[1][i][1] = num[i];
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= cnt; ++j)if (!(st[j]&map[i]))
				for (int k = 1; k <= cnt; ++k) if (!(st[k]&map[i - 1]) && !(st[j]&st[k]))
						for (int s = 1; s <= cnt; ++s) if (!(st[j]&st[s]))
								d[i][j][k] = max(d[i][j][k], num[j] + d[i - 1][k][s]);
	int ans = 0;
	for (int i = 1; i <= cnt; ++i)
		for (int j = 1; j <= cnt; ++j) ans = max(ans, d[n][i][j]);
	printf("%d", ans);
	return 0;
}