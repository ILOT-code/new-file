#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20 + 5;
const int dx[] = {0, 2, 1, -1, -2, -2, -1, 1, 2};
const int dy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};

int ex, ey, mx, my, vis[maxn][maxn];
long long d[maxn][maxn];

bool judge(int x, int y) {
	return x >= 0 && x <= ex && y >= 0 && y <= ey;
}

long long dfs(int x, int y) {
	if (vis[x][y]) return d[x][y];
	vis[x][y] = 1;
	if (!judge(x, y)) return d[x][y] = 0;
	for (int i = 0; i < 9; ++i) if (x == mx + dx[i] && y == my + dy[i]) return d[x][y] = 0;
	if (x == ex && y == ey) return d[x][y] = 1;
	return d[x][y] = dfs(x + 1, y) + dfs(x, y + 1);
}
int main() {
	scanf("%d%d%d%d", &ex, &ey, &mx, &my);
	printf("%lld\n", dfs(0, 0));
	return 0;
}