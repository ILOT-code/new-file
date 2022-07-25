#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
typedef unsigned long long ULL;
int f[maxn][maxn * 10], period[maxn];

void init() {
	for (int n = 2; n < maxn; ++n) {
		f[n][0] = 0, f[n][1] = 1;
		for (int i = 2; ; ++i) {
			f[n][i] = (f[n][i - 2] + f[n][i - 1]) % n;
			if (f[n][i] == 1 && f[n][i - 1] == 0) {
				period[n] = i - 1;
				break;
			}
		}
	}
}

int pow_mod(ULL a, ULL b, int n) {
	if (!b) return 1;
	int t = pow_mod(a, b / 2, n);
	if (b % 2) return (t * t * a) % n;
	else return (t * t) % n;
}
int solve(ULL a, ULL b, int n) {
	if (!a || n == 1) return 0;
	int p = pow_mod(a % period[n], b, period[n]);
	return f[n][p];
}

int main() {
	init();
	ULL a, b;
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%llu%llu%d", &a, &b, &n);
		printf("%d\n", solve(a, b, n));
	}
	return 0;

}