#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;
int n, blocks[maxn][3], dp[maxn][3];

void get_dimensions(int *v, int id, int dim) {
	int idx = 0;
	for (int i = 0; i < 3; ++i)
		if (i != dim) v[idx++] = blocks[id][i];
}

int dpp(int i, int j) {
	int &ans = dp[i][j];
	if (ans > 0) return ans;
	int v[3], v1[3];
	get_dimensions(v, i, j);
	for (int a = 1; a <= n; ++a )
		for (int b = 0; b < 3; ++b) {
			get_dimensions(v1, a, b);
			if (v[0] > v1[0] && v[1] > v1[1]) ans = max(ans, dpp(a, b));
		}
	ans += blocks[i][j];
	return ans;
}

int main() {
	int kase = 0;
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) scanf("%d", &blocks[i][j]);
			sort(blocks[i], blocks[i] + 3);
		}
		memset(dp, 0, sizeof(dp));
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 3; ++j) ans = max(ans, dpp(i, j));
		printf("Case %d: maximum height = %d\n", ++kase, ans);
	}
	return 0;
}