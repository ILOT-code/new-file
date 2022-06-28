#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using LL = long long int;

const int maxn = 1000000 + 10;
int T, cnt, vis[maxn], p[maxn];
LL L, U;

void init() {
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) p[cnt++] = i;
		for (int j = 0; j < cnt && i * p[j] < maxn; ++j) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

int main() {
	init();
	scanf("%d", &T);
	while (T--) {
		LL ans = 0;
		scanf("%lld%lld", &L, &U);
		for (int i = 0; i < cnt && 1LL * p[i] * p[i] <= U; ++i) {
			LL cur = 1LL * p[i] * p[i];
			while (cur <= U) {
				if (cur >= L) ans++;
				cur *= p[i];
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}