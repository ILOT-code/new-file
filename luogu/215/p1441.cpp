#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m, ans, a[20 + 5];
bool f[2000 + 10];

int cal(int x) {
	int cnt = 0;
	for (int i = 0; i < n; ++i, x >>= 1)if (x & 1) cnt++;
	return cnt;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int s = (1 << (n - m)) - 1; s < (1 << n); ++s) if (cal(s) == n - m) {
			memset(f, 0, sizeof(f)); f[0] = 1;
			int tot = 0, res = 0;
			for (int i = 1; i <= n; ++i)if (s & (1 << (i - 1))) {
					tot += a[i];
					for (int j = tot; j >= a[i]; --j) if (f[j - a[i]] && !f[j]) f[j] = 1, res++;
				}
			ans = max(ans, res);
		}
	printf("%d\n", ans);
	return 0;
}