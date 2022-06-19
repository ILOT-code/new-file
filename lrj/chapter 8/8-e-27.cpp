#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;
int a, b, m, n, d[maxn][maxn], dep[maxn];
long long ans, V, S;

int main() {
	while (scanf("%d%d%d%d", &a, &b, &m, &n) == 4) {
		ans = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j) scanf("%d", &d[i][j]);
		if (b < a) swap(a, b);
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j) {
				memset(dep, 0x3f, sizeof(dep));
				for (int r = i; r < m; ++r) {
					int aa = r - i + 1;
					if (aa > b) break;
					for (int c = j; j < n; ++c) {
						int bb = c - j + 1;
						if (bb > b || min(bb, aa) > a) break;
						dep[c] = min(dep[c], d[r][c]);
						if (c) dep[c] = min(dep[c - 1], dep[c]);
						V = 1LL * aa * bb * dep[c];
						S = 1LL * aa * bb;
						ans = max(ans, 1LL * (V / (n * m - S) + dep[c] - (V % (n * m - S) == 0)) * S);
					}
				}
			}
		printf("%lld\n", ans);
	}
}