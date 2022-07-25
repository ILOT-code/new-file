#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int dfs(LL n, int d) {
	int cnt = 1;
	for (int i = d - 2; i >= 0; --i) {
		LL len = i ? 1LL << (i - 1) : 1;
		for (int j = 0; j < cnt; ++j)
			if (n > len) n -= len;
			else return dfs(n, i);
		cnt++;
	}
	return d;
}
int solve(LL n) {
	if (n == 1) return 0;
	n--;
	for (int i = 1; ; ++i) {
		LL len = 1LL << (i - 1);
		if (n > len) n -= len;
		else return dfs(n, i);
	}
}
int main() {
	LL n;
	while (~scanf("%lld", &n) && n) {
		printf("%d\n", solve(n));
	}
	return 0;
}