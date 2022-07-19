#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;

LL n, f[101], num, ans;
int a[101], lim[101];

void prework() {
	f[1] = 1; f[2] = 1;
	for (int i = 3; i <= 90; i++) f[i] = f[i - 1] + f[i - 2];
}

void print(LL sum) {
	int cnt = 0;
	for (int i = 90; i >= 2; i--) {
		if (sum >= f[i]) a[++cnt] = 1, sum -= f[i];
		else a[++cnt] = 0;
	}
	for (int i = 1; i <= cnt; i++) lim[i] = a[90 - i];
}



LL dp[91][2][2];

LL dfs(int digit, int last, bool equal) {
	LL &res = dp[digit][last][equal];
	if (res != -1) return dp[digit][last][equal];
	if (!digit) return res = 0;
	int maxd = 1;
	if (equal) maxd = lim[digit];
	res = 0;
	for (int i = 0; i <= maxd; ++i) {
		if (last == 1 && i == 1) continue;
		bool tem = equal && (i == lim[digit]);
		res += dfs(digit - 1, i, tem) + i;
	}
	return res;
}

int main() {
	while (~scanf("%lld", &n)) {
		memset(dp, -1, sizeof(dp));
		prework();
		if (n == 0) { puts("0"); continue; }
		int w = 1;
		while (n > w * f[w]) {n -= w * f[w], ++ w;}
		num = f[w + 1];
		num += n / w - 1;
		int ws = w - !(n / w), wws = w + (n / w == f[w]);
		n %= w;
		print(num);
		ans = dfs(ws, 0, 1);
		print(num + 1);
		for (int i = wws; i >= wws - n + 1; i--) ans += (lim[i] == 1);
		cout << ans << endl;
	}
	return 0;
}