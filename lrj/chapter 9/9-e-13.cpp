#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 50 + 5;
const int maxv = 10000 + 5;
int n, ns, kase;
int pail[maxn][maxn * maxn], h[maxn];
int order[maxv], dp[maxn * maxn][maxn];
bool vis[maxn][maxn * maxn];
vector<int> heap[maxn * maxn];

int main() {
	while (~scanf("%d", &n)) {
		memset(order, 0, sizeof(order));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= ns; ++i) heap[i].clear();
		ns = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &h[i]);
			for (int j = 1; j <= h[i]; ++j) {
				scanf("%d", &pail[i][j]);
				order[pail[i][j]] = 1;
			}
		}
		for (int i = 1; i < maxv; ++i)
			if (order[i]) order[i] = ++ns;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= h[i]; ++j) {
				int x = order[pail[i][j]];
				if (!vis[i][x]) {
					vis[i][x] = 1;
					heap[x].push_back(i);
				}
			}
		for (int i = 0; i < heap[1].size(); ++i)
			dp[1][heap[1][i]] = heap[1].size();
		for (int x = 2; x <= ns; ++x) {
			int bx = x - 1;
			int s = heap[x].size();
			for (int i = 0; i < heap[x].size(); ++i) {
				int t1 = heap[x][i];
				dp[x][t1] = INF;
				for (int j = 0; j < heap[bx].size(); ++j) {
					int t2 = heap[bx][j];
					if (t1 == t2) dp[x][t1] = min(dp[x][t1], dp[bx][t2] + (s == 1 ? 0 : s));
					else dp[x][t1] = min(dp[x][t1], dp[bx][t2] + s - vis[t2][x]);
				}
			}
		}

		int ans = INF;
		for (int i = 0; i < heap[ns].size(); ++i)
			ans = min(ans, dp[ns][heap[ns][i]]);
		printf("Case %d: %d\n", ++kase, 2 * ans - n - 1);
	}
	return 0;
}