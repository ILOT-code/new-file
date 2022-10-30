//qsort无法保证稳定性，不过却过了。。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;

const int maxn = 500000 + 10;
int n, t[maxn], p[maxn];
PII a[maxn];
inline int lowbit(int x) { return x & (-x); }
long long ans;
void add(int x, int k) {
	while (x <= n) {
		t[x] += k;
		x += lowbit(x);
	}
}
int getsum(int x) {
	int ans = 0;
	while (x >= 1) {
		ans += t[x];
		x -= lowbit(x);
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].fi), a[i].se = i;
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i) p[a[i].se] = i;
	for (int i = 1; i <= n; ++i) {
		add(p[i], 1);
		ans += i - getsum(p[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
