//f(k)=n,n只与k的素因子有关,则因子越小越好。
//题目给出：对任意n,都有f(k)=n;不妨设一个n，n<2^63.
//设f(k1)=n.设k1有m个素因子，分别有a1,a2..am个。
//则k=(a1+a1..+am)!/(a1!*a2!*...am!).
//在m确定的情况下，容易得到，a1=a2=..am=1时，值最小。
//在这种情况下，30!就已经远大于2^64,则素数在前30个中。
//另外 k<2^63,则a1+a2..+am<64;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long LL;
LL target, ans, C[65 + 5][65 + 5];
int cnt, prime[30], vis[100 + 5];

void init() {
	for (int i = 2; i <= 10; ++i)if (!vis[i])
			for (int j = i * i; j <= 100; j += i) vis[j] = 1;
	for (int i = 2; i <= 100; ++i) if (!vis[i]) prime[++cnt] = i;
	for (int i = 1; i <= 65; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
}

void dfs(int pre, LL value, LL ans_tem, int sum, int dep) {
	if (dep >= 24) return;
	if (value == target) {ans = ans_tem; return;}
	LL temp = 1;
	for (int i = 1; i <= pre; ++i) {
		temp *= prime[dep];
		if (ans_tem > ans / temp) break;
		if (C[sum + i][i] > target / value) continue;;
		LL next_v = value * C[sum + i][i];
		dfs(i, next_v, ans_tem * temp, sum + i, dep + 1);
	}
}

int main() {
	init();
	while (~scanf("%llu", &target)) {
		ans = (LL)1 << 63;
		dfs(63, 1, 1, 0, 1);
		if (ans == 1) ans = 2;
		printf("%llu %llu\n", target, ans);
	}
	return 0;
}