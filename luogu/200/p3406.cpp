#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100000 + 5;
int n, m, p[maxn], a[maxn], b[maxn], c[maxn], d[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf("%d", &p[i]);
	for (int i = 1; i <= n - 1; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	int start = 0;
	for (int i = 1; i <= m; ++i) {
		if (i == 1) {start = p[i]; continue;}
		if (p[i] < start) {d[p[i]]++, d[start]--; start = p[i]; continue;}
		if (p[i] > start) {d[start]++, d[p[i]]--; start = p[i]; continue;}
	}
	long long ans = 0, sum = 0;
	for (int i = 1; i <= n - 1; ++i) {
		sum += d[i];
		ans += min(sum * a[i], c[i] + sum * b[i]);
	}
	printf("%lld\n", ans);
	return 0;

}