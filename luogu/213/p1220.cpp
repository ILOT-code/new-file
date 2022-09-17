#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int INF = 0x3f3f3f3f;
int n, c, pos[maxn], power[maxn], sum[maxn], d[maxn][maxn][2], vis[maxn][maxn][2];

int cal(int l, int r, int end, int sta) {
	int t = abs(pos[sta] - pos[end]);
	int exapow = sum[n] - (sum[r] - sum[l - 1]);
	return t * exapow;
}
int dp(int l, int r, int f) {
	if (vis[l][r][f] == 1) return d[l][r][f];
	vis[l][r][f] = 1;
	int& ans = d[l][r][f];
	ans = INF;
	if (l == 1 && r == n) return ans = 0;
	int now = (f == 0 ? l : r);
	if (l > 1) ans = min(ans, dp(l - 1, r, 0) + cal(l, r, l - 1, now));
	if (r < n) ans = min(ans, dp(l, r + 1, 1) + cal(l, r, r + 1, now));
	return ans;
}
int main() {
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &pos[i], &power[i]);
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + power[i];
	printf("%d\n", dp(c, c, 0));
	return 0;
}