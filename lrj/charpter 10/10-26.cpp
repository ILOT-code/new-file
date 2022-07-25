#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000000 + 10;
const int mod = 100000007;
int n, m, vis[maxn], phifac[maxn];

void init() {
	memset(vis, 0, sizeof(vis));
	int temp = sqrt(maxn) + 1e-3;
	for (int i = 2; i <= temp; ++i) if (!vis[i])
			for (int j = i * i; j <= maxn; j += i) vis[j] = 1;
	phifac[1] = 1;//特殊情况
	for (int i = 2; i <= maxn; ++i)
		phifac[i] = (long long)phifac[i - 1] * (vis[i] ? i : i - 1) % mod;
}

int main() {
	init();
	while (~scanf("%d%d", &n, &m) && n) {
		int ans = phifac[m];
		for (int i = m + 1; i <= n; ++i) ans = (long long)ans * i % mod;
		printf("%d\n", (ans - 1 + mod) % mod);
	}
}