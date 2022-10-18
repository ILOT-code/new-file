#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//d[s]表示状态s下，从1号位置到cnt[s]号位置中所抽出的最少人数（即不对应的人数）。
const int maxm = 20 + 3;
const int maxn = 100000 + 10;
int n, m, d[(1 << 20) + 5], sum[maxn][maxm], num[maxm], cnt[(1 << 20) + 5];

void dfs(int p, int s, int f) {
	if (p == m) return;
	int news = s;
	if (f == 1) {
		news = s | (1 << p);
		cnt[news] = cnt[s] + num[p + 1];
	}
	dfs(p + 1, news, 0), dfs(p + 1, news, 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, t; i <= n; ++i) {
		scanf("%d", &t);
		for (int j = 1; j <= m; ++j) sum[i][j] = sum[i - 1][j];
		sum[i][t]++; num[t]++;
	}
	dfs(0, 0, 0), dfs(0, 0, 1);
	memset(d, 0x3f, sizeof(d)); d[0] = 0;
	for (int i = 1; i < (1 << m); ++i) {
		for (int j = 0; j < m; ++j) if (i & (1 << j)) {
				int l = cnt[i ^ (1 << j)], r = cnt[i];
				d[i] = min(d[i], d[i ^ (1 << j)] + r - l - (sum[r][j + 1] - sum[l][j + 1]));
			}
	}
	printf("%d\n", d[(1 << m) - 1]);
	return 0;
}