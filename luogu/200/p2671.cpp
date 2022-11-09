#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int mod = 10007;
int n, m, num[maxn], clo[maxn], cnt[maxn][2], sum[maxn][2];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &num[i]), num[i] %= mod;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &clo[i]);
		cnt[clo[i]][i % 2] = (cnt[clo[i]][i % 2] + 1) % mod;
		sum[clo[i]][i % 2] = (sum[clo[i]][i % 2] + num[i]) % mod;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = (ans + (i % mod) * (((cnt[clo[i]][i % 2] - 2) * num[i] + sum[clo[i]][i % 2]) % mod)) % mod;
	printf("%d\n", ans);
	return 0;
}