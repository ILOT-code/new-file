#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2000 + 5;
int n, dis[maxn][maxn], a[55][55];
int id[55], deg[maxn];

void Build(int& idx) {
	id[1] = ++idx; dis[1][1] = 0;
	for (int i = 2; i <= n; ++i) {
		int len, last;
		for (int j = 1; j <= idx; ++j) {
			len = a[1][i] - dis[1][j];
			bool flag = true;
			for (int k = 2; k < i; ++k)
				if (a[i][k] - dis[j][id[k]] != len) { flag = 0; break; }
			if (flag) { last = j; break; }
		}
		for (int j = 1, u; j <= len; ++j, last = u) {
			u = ++idx;
			deg[u] = 0; dis[u][u] = 0;
			deg[last]++, deg[u]++;
			for (int k = 1; k < idx; ++k) dis[u][k] = dis[k][u] = dis[k][last] + 1;
		}
		id[i] = idx;
	}
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);

		int idx = 0;
		memset(deg, 0, sizeof(deg));
		Build(idx);

		sort(deg + 1, deg + idx + 1);
		for (int i = 1; i <= idx; ++i)
			if (deg[i] != 1) printf("%d%c", deg[i], i == idx ? '\n' : ' ');

	}
	return 0;
}
