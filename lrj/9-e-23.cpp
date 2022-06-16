//要输出最大值，就是按照顺序有[1，a],[a',b]...(a'<=a)之类的按顺序的分拣器覆盖了[1，n].
//设dp[i][j]表示用前i个分拣器（不改变顺序）覆盖到j时，需要最少分拣器个数。
//进行到i，[li,ri]表示第i个分拣器区间。此分拣器的加入仅仅会影响dp[i][ji],
//而其它的j，有dp[i][j]=dp[i-1][j],
//dp[i][ji] = min(dp[i-1][ji],dp[i-1][j']+1) li<=j'<=ri;
//很明显，用滚动数组优化空间，则dp[j] = min(dp[j],dp[j']+1),li<=j'<=ri;
//那么可以采用线段树优化。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000 + 5;
const int INF = 0x3f3f3f3f;
int n, m, minv[maxn << 2], dp[maxn];

void pushup(int rt) {
	minv[rt] = min(minv[rt << 1], minv[rt << 1 | 1]);
}
void build(int rt, int l, int r) {
	if (l == r) {
		minv[rt] = INF;
		return;
	}
	int mid = (r + l) / 2;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}
void change(int rt, int l, int r, int p, int v) {
	if (l == r) {
		minv[rt] = v;
		return;
	}
	int mid = (r + l) / 2;
	if (p <= mid) change(rt << 1, l, mid, p, v);
	else change(rt << 1 | 1, mid + 1, r, p, v);
	pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return minv[rt];
	int mid = (r + l) / 2;
	int r1 = INF, r2 = INF;
	if (L <= mid) r1 = query(rt << 1, l, mid, L, R);
	if (R > mid) r2 = query(rt << 1 | 1, mid + 1, r, L, R);
	return min(r1, r2);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(dp, INF, sizeof(dp));
		build(1, 1, n);
		dp[1] = 0;
		change(1, 1, n, 1, dp[1]);
		for (int i = 1; i <= m; ++i) {
			int l, r;
			scanf("%d%d", &l, &r);
			dp[r] = min(dp[r], query(1, 1, n, l, r) + 1);
			change(1, 1, n, r, dp[r]);
		}
		printf("%d\n", dp[n]);
		if (T) puts("");
	}
	return 0;
}