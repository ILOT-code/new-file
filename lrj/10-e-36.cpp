//数位dp, 每一种合法存在的二进制数都唯一对应一个数。
//对于第i位及更低位的数，唯一的由last(上一位数)，equal(是否相等)确定。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

LL n, f[101], ans;
void init() {
	f[1] = 1; f[2] = 1;
	for (int i = 3; i <= 90; i++) f[i] = f[i - 1] + f[i - 2];
}

int ori[101], rev[101];
void print(LL sum) {
	int cnt = 0;
	for (int i = 90; i >= 2; i--) {
		if (sum >= f[i]) ori[++cnt] = 1, sum -= f[i];
		else ori[++cnt] = 0;
	}
	for (int i = 1; i <= cnt; i++) rev[i] = ori[90 - i];
}

LL dp[91][2][2], kinds[91][2][2];
LL dfs(int digit, int last, bool equal) {
	LL &res = dp[digit][last][equal], &kind = kinds[digit][last][equal];
	if (res != -1) return dp[digit][last][equal];
	if (!digit) {kind = 1; return res = 0;}
	int maxd = 1;
	if (equal) maxd = rev[digit];
	res = kind = 0;
	for (int i = 0; i <= maxd; ++i) {
		if (last == 1 && i == 1) continue;
		bool tem = equal && (i == rev[digit]);
		res += dfs(digit - 1, i, tem) + (i ? kinds[digit - 1][i][tem] : 0);
		kind += kinds[digit - 1][i][tem];
	}
	return res;
}

int main() {
	while (~scanf("%lld", &n)) {
		memset(dp, -1, sizeof(dp));
		init();
		int w = 1;
		while (n > w * f[w]) {n -= w * f[w], ++ w;}
		LL num = f[w + 1] + n / w - 1;
		int wn = w - !(n / w), wl = w + (n / w == f[w]);
		n %= w;
		print(num);
		ans = dfs(wn, 0, 1);
		print(num + 1);
		for (int i = wl; i >= wl - n + 1; i--) ans += rev[i];
		printf("%lld\n", ans);
	}
	return 0;
}