//https://www.luogu.com.cn/problem/solution/UVA1657
//分析后知，就是两张表的变化。
//step[i][j]表示表中(x,y)这个点在第几轮时变为1，那么之后它就一直为0了。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
int n, m, k, step[200 + 5][200 + 5];
int cnt[40000 + 5];
pii ans[10000 + 5], prod[40000 + 5][20];

void play_game(int rnd, int x, int y) {
	int s = x + y, p = x * y;
	bool ok = true;
	if (rnd % 2 == 0) {
		for (int i = 1; 2 * i < s; ++i)
			if (i != x && s - i <= n && step[i][s - i] >= rnd) {ok = false; break;}//!step[i][j]<rnd
	} else {
		for (int i = 0; i < cnt[p]; ++i)
			if (prod[p][i].first != x && step[prod[p][i].first][prod[p][i].second] >= rnd) {ok = false; break;}
	}
	if (ok) step[x][y] = rnd;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		k = 0;
		memset(cnt, 0, sizeof(cnt));
		memset(step, INF, sizeof(step));
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				prod[i * j][cnt[i * j]++] = pii(i, j);
		for (int rnd = 0; rnd <= m; ++rnd)
			for (int i = 1; i <= n; ++i)
				for (int j = i + 1; j <= n; ++j)
					if (step[i][j] == INF) play_game(rnd, i, j);
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (step[i][j] == m) ans[k++] = pii(i, j);
		printf("%d\n", k);
		for (int i = 0; i < k; ++i)
			printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}
