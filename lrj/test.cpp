#include <cstdio>
#include <cstring>
#include <iostream>

#define ll long long

using namespace std;

ll n, f[101], num;

int w;

void prework() {
	f[1] = 1; f[2] = 1;
	for(int i = 3; i <= 90; i++) f[i] = f[i-1] + f[i-2];
} //预处理fib数列

int cnt, a[101];

void print(ll sum) {
	cnt = 0;
	for(int i = 90; i >= 2; i--) {
		if(sum >= f[i]) a[++cnt] = 1, sum -= f[i];
		else a[++cnt] = 0;
	}
} //把一个数字转化成fib数

int lim[101];

ll dp[91][2][91]; 

ll dfs(int digit, int las, ll sum, bool limit) {
	if(!digit) return sum;
	if(!limit && las != -1 && dp[digit][las][sum] != -1) return dp[digit][las][sum];
	int maxn = 1;
	if(limit) maxn = lim[digit];
	ll ans = 0;
	for(int i = 0; i <= maxn; i++) {
		if(i == las && las == 1) continue;
		int p = i;
		bool limm = limit && (i == maxn);
		if(las == -1 && i == 0) p = -1;
		ans += dfs(digit-1, p, sum + (i == 1), limm);
	}
	if(!limit && las != -1) dp[digit][las][sum] = ans;
	return ans;
} //数位dp

ll anss;

int main() {
	while(cin >> n) {
		memset(dp, -1, sizeof(dp));
		prework();
		if(n == 0) {
			printf("0\n");
			continue;
		}
		w = 1;
		while(1) {
			if(n > w * f[w]) n -= w * f[w], ++ w;
			else break;
		}
		num = f[w+1];
		num += n / w - 1; //num即为最后一个完整的数字
		n %= w; //这时的n为不完整的数字位数
		print(num);
		int ws;
		for(int i = 1; i <= cnt; i++) lim[i] = a[90 - i];
		for(int i = cnt; i >= 1; i--) {
			if(lim[i]) {
				ws = i;
				break;
			}
		}
		anss = dfs(ws, -1, 0, 1);
		print(num+1);
		for(int i = 1; i <= cnt; i++) lim[i] = a[90 - i];
		for(int i = cnt; i >= 1; i--) {
			if(lim[i]) {
				ws = i;
				break;
			}
		}
		for(int i = ws; i >= ws - n + 1; i--) anss += (lim[i] == 1);
        //处理最后不完整的数字中1的个数
		cout << anss << endl;
	} 
	return 0;
}