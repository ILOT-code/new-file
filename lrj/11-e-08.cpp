#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = (1 << 10) + 10;
bool have[maxn], g[maxn][maxn];
int n, m;

bool vis[maxn];
int from[maxn];
bool match(int x) {
	for (int i = 0; i < (1 << n); ++i)
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
	for (int i = 0; i < (1 << n); ++i) {
		memset(vis, 0, sizeof(vis));
		res += match(i);
	}
	return res;
}

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		memset(have, 0, sizeof(have));
		memset(g, 0, sizeof(g));
		for (int i = 0; i < m; ++i) {
			char s[15];
			scanf("%s", s);
			int pos = -1, tmp = 0;
			for (int j = 0; j < n; ++j) {
				if (s[j] == '1') tmp |= 1 << j;
				if (s[j] == '*') pos = j;
			}
			have[tmp] = true;
			if (pos != -1) have[tmp | (1 << pos)] = true;
		}
		m = 0;
		for (int i = 0; i < (1 << n); ++i)
			if (have[i]) {
				m++;
				for (int j = 0; j < n; ++j) {
					int tmp = i ^ (1 << j);
					if (have[tmp]) g[i][tmp] = true;
				}
			}

		printf("%d\n", m - hungary() / 2);
	}
	return 0;

}

