//易得一行或一列最多放一个激光。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef pair<int, int> PII;
const int maxn = 100 + 5;
const int INF = 0x3f3f3f3f;

int T, X, Y, row, col, map[maxn][maxn];
PII line[maxn][maxn];

bool vis[maxn], g[maxn][maxn];
int from[maxn];
bool match(int x) {
	for (int i = 1; i <= col ; ++i)
		if (g[x][i] && !vis[i]) {
			vis[i] = true;
			if (from[i] == -1 || match(from[i])) {
				from[i] = x;
				return true;
			}
		}
	return false;
}

int hungary() {
	int res = 0;
	memset(from, -1, sizeof(from));
	for (int i = 1; i <= row ; ++i) {
		memset(vis, 0, sizeof(vis));
		res += match(i);
	}
	return res;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(map, 0, sizeof(map));
		memset(line, 0, sizeof(line));
		int num;
		scanf("%d%d", &X, &Y);
		scanf("%d", &num);
		for (int i = 0, x, y; i < num; ++i) {
			scanf("%d%d", &x, &y);
			map[x][y] = 1;
		}
		scanf("%d", &num);
		for (int i = 0, x, y; i < num; ++i) {
			scanf("%d%d", &x, &y);
			map[x][y] = 2;
		}

		row = col = 0;
		for (int i = 1; i <= X; ++i) {
			bool flag = true;
			for (int j = 1; j <= Y; ++j) {
				if (map[i][j] == 1) {
					if (flag) row++, flag = false;
					line[i][j].first = row;
				}
				if (map[i][j] == 2) flag = true;
			}
		}

		for (int j = 1; j <= Y; ++j) {
			bool flag = true;
			for (int i = 1; i <= X; ++i) {
				if (map[i][j] == 1) {
					if (flag) col++, flag = false;
					line[i][j].second = col;
				}
				if (map[i][j] == 2) flag = true;
			}
		}

		memset(g, 0, sizeof(g));
		for (int i = 1; i <= X; ++i)
			for (int j = 1; j <= Y; ++j)
				if (map[i][j] == 1) g[line[i][j].first][line[i][j].second] = 1;

		printf("%d\n", hungary());
	}
}
