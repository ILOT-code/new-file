#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		long long  n;
		scanf("%lld", &n);
		LL ans = 0, i = 1;
		while (i <= n) {
			int p = n / i, q = n % i;
			ans += p * (1 + q / p);
			i += q / p + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}