#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 40 + 2;
LL n, m, cost[maxn], spre[1 << 21], cnt1, slat[1 << 21], cnt2;
bool cmp(LL a, LL b) {return a > b;}
void dfs(int p, int e, LL sum, LL* a, LL& cnt) {
	if (sum > m) return;
	if (p > e) {a[++cnt] = sum; return;}
	dfs(p + 1, e, sum, a, cnt);
	dfs(p + 1, e, sum + cost[p], a, cnt);
}

int main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", &cost[i]);
	int mid = (1 + n) >> 1;
	dfs(1, mid, 0, spre, cnt1);
	dfs(mid + 1, n, 0, slat, cnt2);
	sort(spre + 1, spre + 1 + cnt1, cmp);
	sort(slat + 1, slat + 1 + cnt2);
	LL ans = 0, p1 = 1, p2 = 1;
	while (p1 <= cnt1) {
		ans += p2 - 1;
		while (p2 <= cnt2 && spre[p1] + slat[p2] <= m) ans++, p2++;
		p1++;
	}
	printf("%lld\n", ans);
	return 0;
}