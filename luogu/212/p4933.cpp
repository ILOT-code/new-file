#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000 + 5;
const int maxd = 2 * 10000 + 5;
const int mod = 998244353;

int n, h[maxn], f[maxn][2 * maxd], vis[2 * maxd];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);

	LL ans = n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j) {
			int d = h[i] - h[j] + maxd;
			f[i][d] = (f[i][d] + (f[j][d] + 1)) % mod;
		}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			int d = h[i] - h[j] + maxd;
			if (vis[d] != i) ans = (ans + f[i][d]) % mod;
			vis[d] = i;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
