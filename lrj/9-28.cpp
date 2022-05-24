//采用的是第一种方法。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 15;
const int maxm = 100 + 5;
int n, m, u[maxm], v[maxm], G[maxn][maxn];
int ind[1 << maxn], d[1 << maxn], best[1 << maxn], clolor[maxn];

bool independent(int curs) {
	for (int i = 0; i < maxn; ++i) if (curs & (1 << i))
			for (int j = i + 1; j < maxn; ++j) if (curs & (1 << j))
					if (G[i][j]) return false;
	return true;
}

int dp(int curs) {
	if (curs == 0) return 0;
	int &ans = d[curs];
	if (ans != -1) return ans;
	ans = maxn + 1;
	for (int s = curs; s; s = (s - 1)&curs) {
		if (ind[s]) {
			int temp = dp(curs ^ s) + 1;
			if (temp < ans) {ans = temp; best[curs] = s;}
		}
	}
	return ans;
}

int main() {
	while (~scanf("%d", &m)) {
		getchar();
		memset(G, 0, sizeof(G));
		int useful = 0;
		for (int i = 0; i < m; ++i) {
			char r1, r2;
			scanf("%c", &r1); getchar();
			scanf("%c", &r2); getchar();
			u[i] = r1 - 'L', v[i] = r2 - 'L';
			G[u[i]][v[i]] = 1;
			G[v[i]][u[i]] = 1;
			useful |= (1 << u[i]);
			useful |= (1 << v[i]);
		}

		memset(ind, 0, sizeof(ind));
		for (int s = useful; s; s = (s - 1)&useful) {
			if (independent(s)) ind[s] = 1;
		}
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(useful) - 2);

		int s = useful, k = 0;
		while (s) {
			for (int i = 0; i < maxn; ++i)
				if (best[s] & (1 << i)) clolor[i] = k;
			k++;
			s = s ^ best[s];
		}
		for (int i = 0; i < m; ++i) {
			if (clolor[u[i]] < clolor[v[i]]) swap(u[i], v[i]);
			printf("%c %c\n", 'L' + u[i], 'L' + v[i]);
		}
	}
	return 0;
}