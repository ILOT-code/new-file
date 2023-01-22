#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
int kk;
LL po[12], xx, yy;

void init() {
	po[0] = 1;
	for (int i = 1; i < 12; ++i) po[i] = po[i - 1] * 2;
}
void solve(LL x, LL y, LL a, LL b, int k) {
	LL l = po[k];
	if (k == 0) return;
	if (x - a <= l / 2 - 1 && y - b <= l / 2 - 1) {
		printf("%lld %lld 1\n", a + l / 2, b + l / 2);
		solve(x, y, a, b, k - 1);
		solve(a + l / 2 - 1, b + l / 2, a, b + l / 2, k - 1);
		solve(a + l / 2, b + l / 2 - 1, a + l / 2, b, k - 1);
		solve(a + l / 2, b + l / 2, a + l / 2, b + l / 2, k - 1);
	} else if (x - a <= l / 2 - 1 && y - b > l / 2 - 1) {
		printf("%lld %lld 2\n", a + l / 2, b + l / 2 - 1);
		solve(a + l / 2 - 1, b + l / 2 - 1, a, b, k - 1);
		solve(x, y, a, b + l / 2, k - 1);
		solve(a + l / 2, b + l / 2 - 1, a + l / 2, b, k - 1);
		solve(a + l / 2, b + l / 2, a + l / 2, b + l / 2, k - 1);
	} else if (x - a > l / 2 - 1 && y - b <= l / 2 - 1) {
		printf("%lld %lld 3\n", a + l / 2 - 1, b + l / 2);
		solve(a + l / 2 - 1, b + l / 2 - 1, a, b, k - 1);
		solve(a + l / 2 - 1, b + l / 2, a, b + l / 2, k - 1);
		solve(x, y, a + l / 2, b, k - 1);
		solve(a + l / 2, b + l / 2, a + l / 2, b + l / 2, k - 1);
	} else {
		printf("%lld %lld 4\n", a + l / 2 - 1, b + l / 2 - 1);
		solve(a + l / 2 - 1, b + l / 2 - 1, a, b, k - 1);
		solve(a + l / 2 - 1, b + l / 2, a, b + l / 2, k - 1);
		solve(a + l / 2, b + l / 2 - 1, a + l / 2, b, k - 1);
		solve(x, y, a + l / 2, b + l / 2, k - 1);
	}
}

int main() {
	init();
	scanf("%d%lld%lld", &kk, &xx, &yy);
	solve(xx, yy, 1, 1, kk);
	return 0;
}