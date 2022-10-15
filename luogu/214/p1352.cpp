#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 6000 + 10;
int n, a[maxn], isroot[maxn], d[maxn][2], vis[maxn][2];
vector<int> sons[maxn];

int dp(int u, int f) {
	if (vis[u][f]) return d[u][f];
	vis[u][f] = 1;
	d[u][f] = f == 1 ? a[u] : 0;
	for (int i = 0; i < sons[u].size(); ++i) {
		int v = sons[u][i];
		if (f == 0) d[u][f] += max(dp(v, 1), dp(v, 0));
		else d[u][f] += dp(v, 0);
	}
	return d[u][f];
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		sons[y].push_back(x);
		isroot[x] = 1;
	}
	int root;
	for (int i = 1; i <= n; ++i) if (!isroot[i]) { root = i; break;}
	printf("%d\n", max(dp(root, 0), dp(root, 1)));
	return 0;
}