#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
int n, m , mod, a[maxn];

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]), a[i] %= mod;
	sort(a, a + n);
	for (int i = 0; i < m; ++i) {
		int k; scanf("%d", &k);
		k %= mod;
		int  p = lower_bound(a, a + n, mod - 1 - k) - a;
		int ans;
		if (a[p] == mod - 1 - k) ans = mod - 1;
		else {
			int ans1 = 0, ans2 = 0;
			if (p) ans1 = a[p - 1] + k;
			ans2 = (a[n - 1] + k) % mod;
			ans = max(ans1, ans2);
		}
		printf("%d\n", ans);
	}
	return 0;
}