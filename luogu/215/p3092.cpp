#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int n, m, cost[maxn], sum[maxn], val[17], allmoney, d[1 << 16], f[1 << 16];

int find(int pos, int money) {
	money += sum[pos - 1];
	int l = pos, r = n + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (sum[mid] <= money) l = mid + 1;
		else r = mid;
	}
	return l - 1;
}
int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i) scanf("%d", &val[i]), allmoney += val[i];
	for (int i = 1; i <= n; ++i) scanf("%d", &cost[i]), sum[i] = sum[i - 1] + cost[i];
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < 1 << m; ++i) {
		for (int j = 0; j < m; ++j) if (i & (1 << j)) {
				int x = i ^ (1 << j);
				if (d[x] == n) break;
				int newpos = find(d[x] + 1, val[j + 1]);
				if (newpos > d[i]) d[i] = newpos, f[i] = f[x] + val[j + 1];
			}
		if (d[i] == n) ans = min(ans, f[i]);
	}
	if (ans == 0x3f3f3f3f) printf("-1\n");
	else printf("%d\n", allmoney - ans);
	return 0;
}