//边逆时针编号，画图之后容易发现，如果一个点可以照到一条边，则两个向量间是顺时针旋转的。
//考虑以i为开始节点，如果说，有一个点可以照到i-2,i-1,i,i+1等，
//那么把它加入到状态规划的话，顺序就乱了，两头的数都会变化。
//如果q[k].r<start+j，那么它回到了已找到的状态，剪掉。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 30 * 2 + 10;
const int maxm = 1000 + 5;
int n, m, dp[maxn];
bool visit[maxn];

struct Point {
	double x, y;
	void read() { scanf("%lf%lf", &x, &y); }
} p[maxn];

struct Light {
	int l, r, c;
	Light(int l = 0, int r = 0, int c = 0): l(l), r(r), c(c) {}
} q[maxm];

bool judge(Point p0, Point p1, Point p2) {
	return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y)) < -eps;
}

Light transform(Point t, int c) {
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < n; ++i)
		if (judge(t, p[i], p[i + 1])) visit[i] = true;
	int l = 0, r = n - 1;
	if (visit[0] && visit[n - 1]) {
		l = n - 1; r = n;
		while (visit[l - 1]) l--;
		while (visit[r - n + 1]) r++;
	} else {
		while (!visit[l]) l++;
		while (!visit[r]) r--;
	}
	return Light(l,r,c);
}
void solve() {
	int ans = INF;
	for (int i = 0; i < n; ++i) {//i是起始点
		memset(dp, INF, sizeof(dp));
		dp[i] = 0;
		for (int j = 0; j < n; ++j) {//枚举长度，采用刷表法。
			int r = i + j;
			for (int k = 0; k < m; ++k) {
				if (q[k].l < i || q[k].l > r || q[k].r < i + j) continue;
				int now = min(i + n, q[k].r + 1);
				dp[now] = min(dp[now], dp[r] + q[k].c);
			}
		}
		ans = min(ans, dp[i + n]);
	}
	if (ans == INF) printf("Impossible.\n");
	else printf("%d\n", ans);
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i) p[i].read();
		p[n] = p[0];
		scanf("%d", &m);
		Point temp;
		int c;
		for (int i = 0; i < m; ++i) {
			temp.read();
			scanf("%d", &c);
			q[i] = transform(temp, c);
		}
		solve();
	}
	return 0;
}