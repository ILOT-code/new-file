//利用交换相邻项的方法，容易得到斜率越大的越先用，则先排序。
//那么dp[i][j][h],表示用前i个向量中选j个，最后高度为h，的面积最大值。
//则dp[i][j][h] = max(dp[i-1][j][h],dp[i-1][j-1][h-p[i].y]+ds),这个向量一定是最后用的，容易算的ds.
//可以用滚动数组简化一个维度，为dp[j][h].
//有很多没必要的计算。用vis[j][h]表示在前i-1个向量里，是否能够拼出有j个向量，高度为h的图形。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
int n, m, H[maxn];
int vis[maxn][maxn * maxn], dp[maxn][maxn * maxn];

struct Point {
	int x, y;
	int area;
	bool operator<(const Point& rhs) {
		return y * rhs.x > x * rhs.y;
	}
} p[maxn];

int main() {
	int T, kase = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &p[i].x, &p[i].y);
			p[i].area = p[i].x * p[i].y;
		}
		sort(p + 1, p + 1 + n);
		H[0] = 0;
		for (int i = 1; i <= n; ++i) H[i] = H[i - 1] + p[i].y;
		memset(dp, 0, sizeof(dp));
		vis[0][0] = kase;
		for (int i = 1; i <= n; ++i)
			for (int j = min(i,m); j >= 1; --j)
				for (int h = p[i].y; h <= H[i]; ++h)if (vis[j - 1][h - p[i].y] == kase) {
						vis[j][h] = kase;
						dp[j][h] = max(dp[j][h], dp[j - 1][h - p[i].y] + 2 * p[i].x * (h - p[i].y) +  p[i].area);
					}
		int ans = 0;
		for (int i = 1; i <= H[n]; ++i) ans = max(ans, dp[m][i]);
		printf("Case %d: %d\n", kase++, ans);
	}
	return 0;
}