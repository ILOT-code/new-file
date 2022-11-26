#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000000;

int n, a[maxn], b[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	LL ans = 0;
	for (int i = 1; i <= n; ++i) ans += 1LL * (a[i] - b[i]) * (a[i] - b[i]);
	printf("%lld", ans);
	return 0;
}