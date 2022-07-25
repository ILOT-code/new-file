#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int k, cnt[5], num[5][6], pai[5], ans[6];
char p[2][6][5];
bool vis[2][26];

void dfs(int col, int xu) {
	if (col == 5) {
		if (xu == k - 1) {
			for (int i = 0; i < 5; ++i) printf("%c", ans[i] + 'A');
			printf("\n");
			return;
		}
		return;
	}
	int t = (k - xu) / pai[col] - ((k - xu) % pai[col] == 0);
	ans[col] = num[col][t];
	dfs(col + 1, xu + t * pai[col]);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		memset(cnt, 0, sizeof(cnt));
		memset(num, 0, sizeof(cnt));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 6; j++)
				scanf("%s", p[i][j]);

		for (int col = 0; col < 5; ++col) {
			memset(vis, 0, sizeof(vis));
			for (int i = 0; i < 2; ++i)
				for (int row = 0; row < 6; ++row)
					vis[i][p[i][row][col] - 'A'] = 1;
			for (int i = 0; i < 26; ++i)
				if (vis[0][i] && vis[1][i])
					num[col][cnt[col]++] = i;
		}
		pai[4] = 1;
		for (int i = 3; i >= 0; --i) pai[i] = pai[i + 1] * cnt[i + 1];
		if (cnt[0]*pai[0] < k) {printf("NO\n"); continue;}
		dfs(0, 0);
	}
	return 0;
}