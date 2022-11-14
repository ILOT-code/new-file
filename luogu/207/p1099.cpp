//设直径左端点L，右端点R。直径上的点从左到右编号。
//di表示到L距离，它是递增的，fi表示到R的距离，它是递减的。
//ti表示直径上一个点的叶子到它的距离，有ti<=min(di,fi).
//设某条路径左边是p1,右边是p2,对于在直径上而不在这路径上的点，有fi<max(dp1,fp2).
//以上是下面代码的依据。实现了线性的复杂度解决问题，并没有用单调队列。
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int>PII;

const int maxn = 300 + 5;
const int INF = 0x3f3f3f3f;
int n, s, d[maxn], fa[maxn];
bool vis[maxn];
vector<PII> G[maxn];

void dfs(int x) {
	for (int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i].first, w = G[x][i].second;
		if (fa[x] == v || vis[v]) continue;
		d[v] = d[x] + w;
		fa[v] = x;
		dfs(v);
	}
}
int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1, u, v, w; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(PII(v, w));
		G[v].push_back(PII(u, w));
	}
	int L = 1, R = 1;
	d[L] = 0; dfs(L);
	for (int i = 1; i <= n; ++i) if (d[i] > d[R]) R = i;
	memset(fa, 0, sizeof(fa));
	d[R] = 0; dfs(R);
	for (int i = 1; i <= n; ++i) if (d[i] > d[L]) L = i;

	int p1 = L, p2 = L;
	int ans = INF;
	while (p1 != 0) {
		while (fa[p2] && d[p1] - d[fa[p2]] <= s) p2 = fa[p2];
		ans = min(ans, max(d[p2], d[L] - d[p1]));
		vis[p1] = 1; p1 = fa[p1];
	}
	for (int i = L; i; i = fa[i]) d[i] = 0, dfs(i);
	for (int i = 1; i <= n; ++i) ans = max(ans, d[i]);
	printf("%d\n", ans);
	return 0;
}