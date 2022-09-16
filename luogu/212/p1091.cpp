#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
const int INF = 0x3f3f3f3f;
int n, h[maxn], d[maxn], f[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	h[0] = h[n + 1] = -INF;
	memset(d, INF, sizeof(d));
	memset(f, INF, sizeof(f));
	d[0] = 0; f[n + 1] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			if (h[i] > h[j]) d[i] = min(d[i], d[j] + i - j - 1);
	for (int i = n; i >= 1; --i)
		for (int j = n + 1; j > i; --j)
			if (h[i] > h[j]) f[i] = min(f[i], f[j] + j - i - 1);
	int ans = INF;
	for (int i = 1; i <= n; ++i) ans = min(ans, d[i] + f[i]);
	printf("%d\n", ans);
	return 0;
}