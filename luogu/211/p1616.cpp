//不加条件优化节点数，会更快。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000000 + 5;

int T, M;
long long f[maxn];

int main() {
	scanf("%d%d", &T, &M);
	memset(f, -1, sizeof(f));
	f[0] = 0;
	for (int i = 1, t, v; i <= M; ++i) {
		scanf("%d%d", &t, &v);
		for (int j = t; j <= T; ++j)
			if (f[j - t] != -1) f[j] = max(f[j], f[j - t] + v);
	}

	long long ans = 0;
	for (int i = T; i >= 0; --i)if (f[i] != -1) ans = max(ans, f[i]);
	printf("%lld\n", ans);
	return 0;
}