#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 10000 + 5;
int col[maxn], link[maxn], du[maxn], n, m, maxd;
vector<int> mp[maxn];

void dfs(int x) {
	for (int i = 0; i < mp[x].size(); i++) {
		int y = mp[x][i];
		if (col[y]) link[col[y]] = x;
	}
	for (int i = 1; i <= maxd; i++)
		if (link[i] != x) {
			col[x] = i;
			break;
		}
	for (int i = 0; i < mp[x].size(); i++) {
		int y = mp[x][i];
		if (!col[y])dfs(y);
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		maxd = 0;
		memset(du, 0, sizeof(du));
		memset(col, 0, sizeof(col));
		memset(link, 0, sizeof(link));
		for (int i = 1; i <= n; i++) mp[i].clear();
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			mp[x].push_back(y); du[x]++;
			mp[y].push_back(x); du[y]++;
			maxd = max(maxd, max(du[x], du[y]));
		}
		if (maxd % 2 == 0) maxd++;
		dfs(1);
		printf("%d\n", maxd);
		for (int i = 1; i <= n; i++) printf("%d\n", col[i]);
		printf("\n");
	}
}