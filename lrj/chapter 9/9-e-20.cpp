//dp[i][j][0/1]，表示前往Ai辆车，前往Bj辆车，最后一辆车的方向是前往A(1)，前往B(0)；
//对于某个d[i][j][1]来讲，最后可能是1,2,3...i辆车作为一趟到达A，则
//d[i][j][1]=min(d[i-1][j][0]+d1,d[i-2][j][0]+d2,...);
//采用填表法复杂度为O(n^4),而刷表法可降为O(n^3).
//车是可以减速的，这是s,t更新的依据，也比较简单。
//两边的车轮流走，那么在方向相同的车中，到达s越小，就越早发。
//采用交换邻项法，设s1,t1,s2,t2,它们同方向，且s2>s1，假设2车先发。
//则发射时间s0>=s2,则容易得到，最后两车都到达的时间s0+max(t1+t2)+10;
//依旧s0发车，1车先发，易得也为s0+max(t1+t2)+10;但是此时的发车时间可能能够更小，则更优。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
const int INF = 0x3f3f3f3f;
int n, na, nb, dp[maxn][maxn][2];
struct Car {
	int s, t;
} A[maxn], B[maxn];

int solve() {
	memset(dp, INF, sizeof(dp));
	dp[0][0][1] = dp[0][0][0] = 0;
	for (int i = 0; i <= na; ++i)
		for (int j = 0; j <= nb; ++j) {
			int s = dp[i][j][0], end = 0;
			for (int k = i + 1; k <= na; ++k) {
				s = max(A[k].s, s);
				end = max(s + A[k].t, end);
				dp[k][j][1] = min(dp[k][j][1], end);
				s += 10, end += 10;
			}
			s = dp[i][j][1], end = 0;
			for (int k = j + 1; k <= nb; ++k) {
				s = max(B[k].s, s);
				end = max(s + B[k].t, end);
				dp[i][k][0] = min(dp[i][k][0], end);
				s += 10, end += 10;
			}
		}
	return min(dp[na][nb][0], dp[na][nb][1]);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		na = nb = 0;
		scanf("%d", &n);
		char c[5];
		for (int i = 0; i < n; ++i) {
			scanf("%s", c);
			if (c[0] == 'A') {
				na++;
				scanf("%d%d", &A[na].s, &A[na].t);
			} else {
				nb++;
				scanf("%d%d", &B[nb].s, &B[nb].t);
			}
		}
		printf("%d\n", solve());
	}
	return 0;
}