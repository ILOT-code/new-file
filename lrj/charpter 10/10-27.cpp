#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxa = 2000 + 5;
int a, b, phi[maxa];

void init() {
	phi[1] = 1;
	for (int i = 2; i < maxa; ++i)if (!phi[i])
			for (int j = i; j < maxa; j += i) {
				if (!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	init();
	while (~scanf("%d%d", &a, &b) && a) {
		long long ans = 0;
		for (int x = 1; x <= a; ++x) {
			int k = b / x;
			ans += phi[x] * k;
			for (int y = k * x + 1; y <= b; ++y)
				if (gcd(x, y) == 1) ans++;
		}
		ans = ans * 4 + 4;
		long long N = (long long)(2 * a + 1) * (2 * b + 1) - 1;
		printf("%.7lf\n", (double)ans / N);
	}
	return 0;
}

