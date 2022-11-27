#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
const int maxn = 5000 + 5;
int n, m;

vector<int> G[maxn];
vector<PII> e;
int ban_u, ban_v;
int ans[maxn], cnt;
bool vis[maxn];
void dfs(int u, int f) {
	vis[u] = 1; ans[cnt++] = u;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (vis[v]) continue;
		if (f && ((u == ban_u && v == ban_v) || (u == ban_v && v == ban_u))) continue;
		dfs(v, f);
	}
}
void solve1() {
	dfs(1, 0);
	for (int i = 0; i < n; ++i) printf("%d ", ans[i]);
}
void update(int* ret) {
	bool flag = false;
	if (cnt == n)
		for (int i = 0; i < n; ++i) {
			if (ans[i] < ret[i]) {flag = true; break;}
			if (ans[i] > ret[i]) {flag = false; break;}
		}
	if (flag) for (int i = 0; i < n; ++i) ret[i] = ans[i];
}
void solve2() {
	int ret[maxn]; ret[0] = 0x3f3f3f3f;
	for (int i = 0; i < m; ++i) {
		cnt = 0; memset(vis, 0, sizeof(vis));
		ban_u = e[i].first, ban_v = e[i].second;
		dfs(1, 1);
		update(ret);
	}
	for (int i = 0; i < n; ++i) printf("%d ", ret[i]);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
		e.push_back(PII(u, v));
	}
	for (int i = 1; i <= n; ++i) sort(G[i].begin(), G[i].end());
	if (m == n - 1) solve1();
	if (m == n) solve2();
	return 0;
}