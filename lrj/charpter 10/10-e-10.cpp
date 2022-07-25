#include <iostream>
#include <cstdio>
using namespace std;

const int maxn = 1000 + 10;
int n, kase, ans[maxn];
const int MOD = 1e9 + 7;

void init() {
	ans[1] = ans[2] = 1;
	for (int i = 3; i < maxn; ++i)
		for (int j = 1; j < i; ++j)
			if ((i - 1) % j == 0)
				ans[i] = (ans[i] + ans[j]) % MOD;
}

int main() {
	init();
	while (~scanf("%d", &n) && n)
		printf("Case %d: %d\n", ++kase, ans[n]);
	return 0;
}