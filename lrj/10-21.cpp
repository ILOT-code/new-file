#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
int T, kase, n, k;

LL gcd(LL a, LL b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		LL b = LL(1) << k;
		LL a = b - k - 1;
		LL g = gcd(a, b);
		a /= g; b /= g;
		printf("Case #%d: %lld/%lld\n", ++kase, a, b);
	}
	return 0;
}