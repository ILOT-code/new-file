#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };
int m, n, map[maxn][maxn], d[maxn][maxn], vis[maxn][maxn];

bool judge(int r, int c, int nr, int nc) {
	if (nr < 0 || nr >= m || nc < 0 || nc >= n) return false;
	if (map[r][c] <= map[nr][nc]) return false;
	return true;
}

int dp(int r, int c) {
	if (vis[r][c]) return d[r][c];
	vis[r][c] = 1;
	int &ans = d[r][c];
	ans = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (judge(r, c, nr, nc)) ans = max(ans, 1 + dp(nr, nc));
	}
	return ans;
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) scanf("%d", &map[i][j]);
	int ans = 1;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) ans = max(ans, dp(i, j));
	printf("%d\n", ans);
	return 0;
}
