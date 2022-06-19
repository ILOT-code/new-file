//复杂度为O(n^3)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int INF = 1 << 30;
int n, L, a[maxn], vis[maxn][maxn], d[maxn][maxn];

int dp(int i, int j) {
	if (vis[i][j]) return d[i][j];
	vis[i][j] = 1;
	if (i >= j - 1) return d[i][j] = 0;
	int &ans = d[i][j];
	ans = INF;
	for (int k = i + 1; k <= j - 1; ++k)
		ans = min(ans, dp(i, k) + dp(k, j) + a[j] - a[i]);
	return ans;
}

int main() {
	while (~scanf("%d%d", &L, &n) && L) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[0] = 0; a[n + 1] = L;
		memset(vis, 0, sizeof(vis));
		printf("The minimum cutting is %d.\n", dp(0, n + 1));
	}
	return 0;
}