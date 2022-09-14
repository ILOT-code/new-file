#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int T, kase, n;
int deg[maxn], maxd[maxn];

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(deg, 0, sizeof(deg));
		memset(maxd, 0, sizeof(maxd));
		scanf("%d", &n);
		int ans = 0;
		for (int i = 0, u, v, w; i < n - 1; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			deg[u] += w; maxd[u] = max(maxd[u], w);
			deg[v] += w; maxd[v] = max(maxd[v], w);
			ans += w;
		}

		for (int i = 1; i <= n; ++i) {
			if (maxd[i] <= (deg[i] >> 1)) ans -= deg[i] >> 1;
			else ans -= deg[i] - maxd[i];
		}
		printf("Case #%d: %d\n", ++kase, ans);
	}
	return 0;
}
