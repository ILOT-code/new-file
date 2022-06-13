//设n条绳分成x1个片段，此时质量最大的半段的最小值是m1，同理有x2,m2;
//在分的段数的奇偶性不确定的情况下，随着x的增加，m不一定减少。
//如1 1 100 100 1 1.x1 = 2时，m1=102; 而mx2=3时，m2=200；
//但是容易得到，当分的段数的奇偶性确定后，m随着x的增加而减少，因此可以用二分法。
//上面其实就描述了一种函数关系，自变量x，因变量m.这种关系时不增的。
//这里的dp其实就是求在图像上，点(x',m)右边最接近的一个整数。
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