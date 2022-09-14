#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int INF = 0x3f3f3f3f;
int n, A[maxn], B[maxn], d[maxn], g[maxn], to[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &A[i]), to[A[i]] = i;
	for (int i = 1; i <= n; ++i) scanf("%d", &B[i]);
	for (int i = 1; i <= n; ++i) B[i] = to[B[i]];

	for (int i = 1; i <= n; ++i) g[i] = INF;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int k = lower_bound(g + 1, g + 1 + n, B[i]) - g;
		d[i] = k;
		ans = max(ans, k);
		g[k] = B[i];
	}
	printf("%d\n", ans);
}