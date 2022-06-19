#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 500 + 5;
int n, s[maxn], maxv[maxn][maxn], minv[maxn][maxn], uniq[maxn][maxn], dp[maxn][maxn];
int pre[maxn], pos[maxn], ans[maxn];

int dfs(int left, int right) {
	int &ans = dp[left][right];
	if (ans < INF) return ans;
	if (left == right) return ans = 0;
	for (int i = left; i < right; ++i) {
		int t = max(minv[left][i], minv[i + 1][right]);
		int num = 0;
		if (minv[left][i] < t)
			for (int j = left; j <= i; ++j) num += (s[j] < t);
		else
			for (int j = i + 1; j <= right; ++j) num += (s[j] < t);
		ans = min(ans, dfs(left, i) + dfs(i + 1, right) + right - left + 1 - num);
	}
	return ans;
}

int main() {
	while (~scanf("%d", &n)) {
		memset(pos, -1, sizeof(pos));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &s[i]);
			uniq[i][i] = 1;
			maxv[i][i] = minv[i][i] = s[i];
			pre[i] = pos[s[i]];
			pos[s[i]] = i;
		}
		for (int i = 1; i < n; ++i)
			for (int j = i + 1; j <= n; ++j) {
				maxv[i][j] = max(maxv[i][j - 1], s[j]);
				minv[i][j] = min(minv[i][j - 1], s[j]);
				uniq[i][j] = uniq[i][j - 1] && (pre[j] < i);
			}
		memset(dp, INF, sizeof(dp));
		memset(ans, INF, sizeof(ans));
		ans[0] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j)
				if (ans[i - 1] < INF && uniq[i][j] && maxv[i][j] == j - i + 1)
					ans[j] = min(ans[j], ans[i - 1] + dfs(i, j));
		if (ans[n] < INF) printf("%d\n", ans[n]);
		else printf("impossible\n");
	}
	return 0;
}