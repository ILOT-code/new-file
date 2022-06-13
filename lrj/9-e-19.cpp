//设在半段重量为m1时，n个绳的最小分段为x1,同理m2,x2;
//在分的段数不确定的情况下，随着m的增加，x不一定减少。
//如1 1 100 100 1 1.m1=102时，x1 = 2; 而m2= 200时，x2=3；
//但是容易得到，当分的段数的奇偶性确定后，x随着m增加而不增。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 40000 + 5;
const int INF = 0x3f3f3f3f;
int n, m, d, sum[maxn], dp[maxn][2];

bool judge(int x) {
	memset(dp, INF, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 2; i <= n; i += 2) {
		for (int j = 1; j <= d && j <= i / 2; ++j) {
			if (sum[i] - sum[i - j] > x) break; 
			if (sum[i - j] - sum[i - 2 * j] > x) continue;
			dp[i][0] = min(dp[i][0], dp[i - 2 * j][1] + 1);
			dp[i][1] = min(dp[i][1], dp[i - 2 * j][0] + 1);
		}
	}
	return dp[n][(m - 1) & 1] < m;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &d);
		for (int i = 1; i <= n; ++i) {
			int t;
			scanf("%d", &t);
			sum[i] = sum[i - 1] + t;
		}
		if ((n & 1) || n > 2 * d * (m - 1) || n < 2 * (m - 1)) {
			printf("BAD\n");
			continue;
		}

		int l = 1, r = sum[n], mid = l + (r - l) / 2;
		while (l < r) {
			if (judge(mid)) r = mid;
			else l = mid + 1;
			mid = l + (r - l) / 2;
		}
		printf("%d\n", l);
	}
	return 0;
}