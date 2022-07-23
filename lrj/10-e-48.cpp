#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
int kase;
LL n, ans;

int main() {
	while (~scanf("%lld", &n)) {
		ans = 0;
		for (LL i = 1; i * i * i <= n; ++i)
			for (LL j = i; i * j * j <= n; ++j) {
				LL k = n / i / j - j + 1;
				if (i == j) ans += (k - 1) * 3LL + 1ll;
				else ans += (k - 1) * 6LL + 3LL;
			}
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}