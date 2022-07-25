//即使是在int型范围内，但取负号可能超过。
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int solve(long long n) {
	bool flag = false;
	if (n < 0) {
		n = -n;
		flag = true;
	}

	int ans = 0;
	int m = sqrt(n) + 1e-3;
	for (int i = 2; i <= m; ++i) {
		int temp = 0;
		while (n % i == 0) {
			n /= i;
			temp++;
		}
		ans = gcd(ans, temp);
	}
	if (n > 1) ans = 1;
	if (flag) while ((ans & 1) == 0) ans >>= 1;
	return ans;
}

int main() {
	LL n;
	while (~scanf("%lld", &n) && n) {
		printf("%d\n", solve(n));
	}
	return 0;
}